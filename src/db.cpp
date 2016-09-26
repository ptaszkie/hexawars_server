#include "db.hpp"

#include <iostream>
#include <thread>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

// static initialization
mongocxx::instance DB::mongodbInstance{};
std::list<dbClient> DB::clientList;
std::mutex DB::m_clientList;

bool DB::is_initialized= false;
unsigned DB::poolSize= 0;

//##############################################################################

DB::DB(dbClient&& client, hax) noexcept
    : client(std::move(client)) 
{
}

DB::~DB() noexcept {}

void DB::init(unsigned pool_size) noexcept
{
    std::lock_guard<std::mutex> lock(m_clientList);
    if(is_initialized)
        return;

    // fill the pool
    for(int i= 0; i < pool_size; ++i) {
        clientList.push_back(std::make_unique<mongocxx::client>(mongocxx::uri{}));
    }

    poolSize= pool_size;
    is_initialized= true;
}

std::unique_ptr<DB> DB::getConnection() noexcept
{
    dbClient p;

    while(true) {
        if(!clientList.empty()) {
            std::lock_guard<std::mutex> lock(m_clientList);
            if(!clientList.empty()) {
                p= std::move(clientList.front());
                clientList.pop_front();
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return std::make_unique<DB>(std::move(p), hax{});
}

void DB::returnConnection() noexcept
{
    std::lock_guard<std::mutex> lock(m_clientList);
    clientList.push_back(std::move(client));
}

//##############################################################################
// HELPERS FUNCTION
//##############################################################################
std::shared_ptr<Player> DB::findPlayer(const std::string &id, connection_hdl hdl) noexcept
{
    if(id.length() != 24) {
        std::cout << "Error: DB::findPlayer(): id has wrong lenght.\n\n" << std::flush;
        return nullptr;
    }

    auto col= (*client)["hexawars"]["users"];

    // set fields to return
    bsoncxx::builder::stream::document filter_user{};
    filter_user << "_id"    << 1 
                << "name"   << 1 
                << "email"  << 1
                << "units"  << 1;

    mongocxx::options::find fopts{};
    fopts.projection(filter_user.view());

    // set looking for id
    bsoncxx::builder::stream::document search_info{};
    search_info << "_id" << bsoncxx::oid{ id };

    auto cur= col.find_one(search_info.view(), fopts);

    if(!cur)
        return nullptr;

    auto view = cur->view();
    
    // REMOVE: just for tests
    //std::cout << bsoncxx::to_json(view) << std::endl;
    
    std::string name = view["name"].get_utf8().value.to_string();
    
    return std::make_shared<Player>(name, hdl);
}

/*

Player* DB::findPlayer(string id)
{
    auto col = (*m_dbClient)["hexawars"]["users"];
    auto cur = col.find({});

    // pcje zapytania
    mongocxx::options::find fopts{};

    bsoncxx::builder::stream::document doc{};
    doc << "_id" << 1
        << "name" << 1
        << "email" << 1
        << "units" << 1;

    fopts.projection(doc.view());

// wyswietlenie dla upewnienia sie, co pobrane zostanie
    bsoncxx::builder::stream::document ser{};
    ser << "_id" << id;


    auto cursor = col.find_one(ser, fopts);
    cout << bsoncxx::to_json(cursor);

    return nullptr;


//    for(auto&& c: cur)
//        cout << bsoncxx::to_json(c) << endl;
}*/
