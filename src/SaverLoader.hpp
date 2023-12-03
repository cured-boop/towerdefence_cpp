/*//reference in Game. Needs to be implemented. Handles I/O and state
management.
//required to instal (nlohmann/json) @ nlohmann/json GitHub repository
#ifndef SAVERLOADER_HPP
#define SAVERLOADER_HPP

#include "Game.hpp" // Include necessary header for Game class
// TODO #include <json.hpp>  Include the nlohmann/json library

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