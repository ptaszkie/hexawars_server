#ifndef WEBSOCKETSRV_HPP
#define WEBSOCKETSRV_HPP

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/tags/tagged.hpp>

#include <map>
#include <string>
#include <mutex>

#include "db.hpp"
#include "player.hpp"

using websocketpp::connection_hdl;
using server = websocketpp::server<websocketpp::config::asio>;
using message_ptr = server::message_ptr;

using namespace boost::bimaps;

// for bimap tags
struct name{};
struct con_hdl{};
struct player_obj{};

// bimap <std::map<name, conn_hdl>, std::map<conn_hdl, name>, Player_class> 
using conn_bimap = boost::bimap<
    set_of<tagged<std::string, name>>,
    set_of<tagged<connection_hdl, con_hdl>, std::owner_less<connection_hdl>>,
    with_info<tagged<std::shared_ptr<Player>, player_obj>>
    >;
    
//using playerOnline = conn_bimap::value_type;
using playerOnline = conn_bimap::value_type;
//typedef conn_bimap::value_type playerOnline;

/**
 * @class WebSocketSrv
 * @author Quave
 * @date 30/08/16
 * @file websocketsrv.hpp
 * @brief WebSocket service
 */
class WebSocketSrv {
    static server srv;      /**< server instance */

    //static std::map<std::string, std::unique_ptr<Player>> playersOnline;
    static conn_bimap playersOnline;    /**< list of connected players - bimap */
    static std::mutex m_playersOnline; 

public:
    /**
     * @brief Initialization
     * @param port WS listening port. Default is 9002.
     */
    static bool init(unsigned port= 9002) noexcept;
    
    /**
     * @brief Run WebSocket server
     */
    static void run() noexcept;
    
    /**
     * @brief Stop WebSocket server 
     */
    static void stop() noexcept;

    /** 
     * @brief Close all connections
     */
    static bool sendClose() noexcept;
    
    /**
     * @brief Send msg to all
     */
    static bool broadcastMsg() noexcept;
    
    /**
     * @brief How many players are online
     * @return 
     */
    static inline unsigned getOnline() { return playersOnline.size();}
    
    /**
     * @brief Get information about signed in player
     * @param id
     */
    static std::shared_ptr<Player> getPlayerByName(std::string nick);
    
    /**
     * @brief Get information about signed in player
     * @param id
     */
    static std::shared_ptr<Player> getPlayerByHdl(connection_hdl);
    
private:
    /**
     * @brief Validate handler
     * 
     * Validate incoming connections. Add information about connected player to
     * playersOnline list.
     * 
     * @param hdl
     * @ return true if connection has valid id, alse false
     */
    static bool on_validate(connection_hdl hdl) noexcept;
    
    /**
     * @brief Validate id from query
     * @param id
     */
    static bool validateID(std::string &query);
    
    /**
     * @brief Connection close handler
     * 
     * Remove player from playersOnline.
     * 
     * @param hdl
     */
    static void on_close(connection_hdl hdl) noexcept;
    
    
    /**
     * @brief Fail handler
     * @param hdl
     */
    static void on_fail(connection_hdl hdl) noexcept;
    
    
    /**
     * @brief Incoming message handler
     * 
     * @param hdl
     * @param msg
     */
    static void on_msg(connection_hdl hdl, message_ptr msg) noexcept;
    
    
};

#endif // WEBSOCKETSRV_HPP