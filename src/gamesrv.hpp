#ifndef GAMESRV_HPP
#define GAMESRV_HPP

#include <thread>
#include <queue>
#include <memory>
#include <mutex>
#include "msg.hpp"

class GameSrv {
    static bool is_initialized;
    static bool is_running;
    static std::thread ws_thread;
    static std::queue<Msg> msgQueue;
    static std::mutex m_msgQueue;

public:
    /**
     * @brief Starts game server
     *
     * Game server is automatically initiate during first call of this function.
     */
    static void start();

    /**
     * @brief Stops game server
     */
    static void stop();
    
    /**
     * @brief Add msg to MsgQueue
     */
    static void addMsg(Msg m);

private:
    GameSrv()= delete;
    ~GameSrv()= delete;

    /**
     * @brief Initiate game server
     */
    static void init();
    static void run();
};

#endif // GAMESRV_HPP

/*

mongocxx::instance ist{};
mongocxx::client conn{mongocxx::uri{}};

// dla wybrania odpowiednich pol z dokumentow
mongocxx::options::find fopts{};

// wybor kolekcji
auto col = conn["hexawars"]["users"];

// nowy dokument bson dla filtra pol
bsoncxx::builder::stream::document doc{};
doc << "_id" << 1
     << "name" << 1
     << "email" << 1;
fopts.projection(doc.view());

// wyswietlenie dla upewnienia sie, co pobrane zostanie
cout << "dokument:\n" << bsoncxx::to_json(doc) << endl << endl;
auto cursor = col.find_one({}, fopts);

// wymagane dla find_one
auto view = cursor->view();

// wyswietlamy obiekt pobrany ;)
cout << bsoncxx::to_json(view) << endl;


auto id = view["name"].get_utf8().value.to_string();
auto nm = view["_id"].get_oid().value.to_string();

cout << "name -> " << id << endl;
cout << "id -> " << nm << endl;



auto pl = player(id, nm);
cout << pl.info();

// dla find wyswietlanie poszczegolnych dokumentow ;)
//    for(auto&& el : cursor){
//        std::cout << bsoncxx::to_json(el) << std::endl;
//        std::cout << "name -> " << el["name"].get_utf8().value.to_string() << std::endl;
//    }

//auto el = cursor.view();
//std::cout << bsoncxx::to_json(el) << std::endl;

cout.flush();

SRV.set_message_handler(&on_message);

SRV.init_asio();
SRV.listen(9002);
SRV.start_accept();

SRV.run();
*/