#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <websocketpp/common/connection_hdl.hpp>

using websocketpp::connection_hdl;

class Player {
    std::string name;
    connection_hdl hdl;

public:
    explicit Player(std::string name, connection_hdl hdl) noexcept
        :name(name), hdl(hdl){};
    
    ~Player(){};
    
    /**
     * @brief Get player name. 
     * @return Player name
     */
    std::string getName() {return name;}
    
    /**
     * @brief Get player connection handler
     * @return 
     */
    connection_hdl getConnectionHdl(){return hdl;}
    
    /**
     * @brief get player information as JSON string
     */
    std::string toJSON() noexcept;
};

#endif // PLAYER_HPP