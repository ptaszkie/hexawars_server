#ifndef DB_HPP
#define DB_HPP

#include <list>
#include <mutex>
#include <memory>
#include "player.hpp"

//#include <bsoncxx/builder/stream/document.hpp>
//#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <websocketpp/common/connection_hdl.hpp>

using dbClient = std::unique_ptr<mongocxx::client>;

using websocketpp::connection_hdl;

/**
 * @class DB
 * @author Quave
 * @date 1/06/16
 * @file db.hpp
 * @brief Class services database connections
 *
 * Before use the class must be initalized by init() function.
 */
class DB {
    // static members
    static mongocxx::instance mongodbInstance;
    static std::list<dbClient> clientList;
    static std::mutex m_clientList;

    static bool is_initialized;
    static unsigned poolSize;

    // object members
    dbClient client;

    // hax for make_unique, read DB(dbClient&&, hax) description for more info.
    struct hax {};

public:
    /**
     * @brief Constructor
     *
     * In c++11/14 std::make_unique and std::make_shared can't acces to
     * private constructors, so we need to cheat ;) Thus we create private
     * member struct (hax) and use it in public constructor.
     */
    explicit DB(dbClient&& client, hax) noexcept;

    /**
     * @brief Destructor
     */
    ~DB() noexcept;

    /**
     * @brief Initialization
     *
     * Must be call before use others methods.
     * Create connections pool. Default size of pool is 10.
     *
     * @param poolSize Pool size
     */
    static void init(unsigned poolSize= 10) noexcept;

    /**
    * @brief Get database connection.
    *
    * Function wait untill any connection is avaible in the pool.
    *
    * @return DB object
    */
    static std::unique_ptr<DB> getConnection() noexcept;

    /**
     * @brief Search signed up player by id.
     *
     * @param id ID of searching player.
     * @return Player Class with informations about player or nullptr if not finded.
     */
    std::shared_ptr<Player> findPlayer(const std::string &id, connection_hdl hdl) noexcept;

private:
    /**
    * @brief Return connection to the pool.
    */
    void returnConnection() noexcept;
};

#endif // DB_HPP

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
