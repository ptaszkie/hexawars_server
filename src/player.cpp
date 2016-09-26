#include "player.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

std::string Player::toJSON() noexcept
{
    bsoncxx::builder::stream::document pl;
    pl << "name" << name;
    
    return bsoncxx::to_json(pl);
}
