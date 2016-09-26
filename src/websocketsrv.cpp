#include "websocketsrv.hpp"
#include <iostream>

#include <iomanip>
#include <ctime>

// static initialization
server WebSocketSrv::srv;
//std::map<std::string, std::unique_ptr<Player> > WebSocketSrv::playersOnline;
conn_bimap WebSocketSrv::playersOnline;
std::mutex WebSocketSrv::m_playersOnline;

bool WebSocketSrv::init(unsigned port) noexcept
{
    srv.init_asio();

    // logs
    srv.get_alog().set_channels(websocketpp::log::alevel::none);
    srv.get_elog().set_channels(websocketpp::log::elevel::all);
    srv.get_alog().set_ostream(&std::cout);
    srv.get_elog().set_ostream(&std::cout);

    // handlers
    srv.set_validate_handler(&WebSocketSrv::on_validate);
    // srv.set_fail_handler(&WebSocketSrv::on_fail);
    srv.set_close_handler(&WebSocketSrv::on_close);
    srv.set_message_handler(&WebSocketSrv::on_msg);

    // uruchomienie nasluchiwania
    try {
        srv.listen(port);
    }
    catch(websocketpp::exception const& e) {
        std::cout << "Error: WebSocketSrv => init => listen():" << e.what() << std::endl;
        return false;
    }

    // uruchomienie przyjmowania połączeń
    websocketpp::lib::error_code ec;
    srv.start_accept(ec);
    if(ec) {
        std::cout << "Error: WebSocketSrv => init => accept(): " << ec.message() << std::endl;
        return false;
    }

    return true;
}

void WebSocketSrv::run() noexcept
{
    try {
        srv.run();
    }
    catch(websocketpp::exception const& e) {
        std::cout << "Error: " << e.what() << std::endl;
        // return false;
    }

    // return true;
}

void WebSocketSrv::stop() noexcept
{
    std::cout << "Stopping WebSocket server.\n";
    websocketpp::lib::error_code ec;
    srv.stop_listening(ec);
    if(ec) {
        std::cout << "ERROR: " << ec.message() << std::endl;
        return;
    }

    std::string data = "Closing connections...";
    for(auto&& player : playersOnline.by<con_hdl>()) {
        websocketpp::lib::error_code ec;
        
        std::cout << player.get<name>() << std::endl;
       // srv.close(player.get<con_hdl>()->getConnectionHdl(), websocketpp::close::status::normal, data, ec);
        if(ec) {
            std::cout << "ERROR: " << ec.message() << std::endl;
        }
    }

    srv.stop();
}

bool WebSocketSrv::on_validate(connection_hdl hdl) noexcept
{
    bool result = false;
    auto        con   = srv.get_con_from_hdl(hdl);
    std::string query = con->get_uri()->get_query(),
                id    = query,
                log;
    
    if(result = validateID(id)){
        
        if(auto pl = DB::getConnection()->findPlayer(id, hdl)) {
        
            std::lock_guard<std::mutex> lock(m_playersOnline);
            auto ret = playersOnline.insert(playerOnline(pl->getName(), hdl, pl));
            // gracz aktualnie zalogowany
            if(!ret.second){
                log = "*** Player " + pl->getName() + " [" + con->get_host() + "] actually logged in. Connection refused. ***\n";
                result = false;
            }
            else {
                log = "Player " + pl->getName() + " [" + con->get_host() + "] connected.\n";
            }
        } else {
            
            log = "*** Connection from [" + con->get_host() + "] refused [Player id doesn't exist in DB] ***\n";
            
            result = false;
        }
    } else {
        log = "*** Connection from [" + con->get_host() + "] refused [ID doesn't found or wrong lenght] ***\n";
    }
        
    std::cout << log << std::flush;
    
    return result;
}

void WebSocketSrv::on_close(connection_hdl hdl) noexcept{
    auto f = getPlayerByHdl(hdl);
    
    playersOnline.right.erase(hdl);
    
}

void WebSocketSrv::on_msg(connection_hdl hdl, message_ptr msg) noexcept
{
    std::string m = msg->get_payload();
    auto        p = getPlayerByHdl(hdl);
    std::cout << p->getName() << " send msg: " << m << std::endl;
}

std::shared_ptr<Player> WebSocketSrv::getPlayerByName(std::string nick)
{
    std::lock_guard<std::mutex> lock(m_playersOnline);
    return playersOnline.by<name>().info_at(nick);
}

std::shared_ptr<Player> WebSocketSrv::getPlayerByHdl(connection_hdl hdl)
{
    std::lock_guard<std::mutex> lock(m_playersOnline);
    return playersOnline.by<con_hdl>().info_at(hdl);
}

bool WebSocketSrv::validateID(std::string& query)
{
    // remove "id=" from query
    int tmp = query.find("id=");
    if(!query.empty() &&  tmp != -1) {
    
        query = query.substr(tmp + 3);
        
        // remove another parameters
        tmp = query.find("&");
        if(tmp != -1)
            query.erase(tmp);
    }
    
    if(query.length() == 24)
        return true;
    
    return false;
}
