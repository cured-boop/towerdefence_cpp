#ifndef SAVERLOADER_HPP
#define SAVERLOADER_HPP

#include "Game.hpp" // Include necessary header for Game class
#include "json.hpp" 

using namespace nlohmann;

class SaverLoader {
public:
    SaverLoader(Game* game);

    void save();
    nlohmann::json load();
    nlohmann::json loadConfig();

private:
    Game* game;
};

#endif // SAVERLOADER_HPP*/