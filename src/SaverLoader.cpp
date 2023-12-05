/* #include "SaverLoader.hpp"
#include "Tower.hpp" // Include necessary header for Tower class

#include <fstream>
#include <iostream>

SaverLoader::SaverLoader(Game* game) : game(game) {}

void SaverLoader::save() {
    nlohmann::json JSON = {
        {"wave", game->getWaveIndex()},
        {"gold", game->getOverall()->getGold()},
        {"hp", game->getOverall()->getHp()},
        {"towers", {}}
    };

    for (const auto& tower : game->getTowersBuffer()) {
        JSON["towers"].push_back({
            {"type", tower->getType()},
            {"dmg", tower->getDmg()},
            {"range", tower->getRange()},
            {"pos", {{"x", tower->getPos().x}, {"y", tower->getPos().y}}}
        });
    }

    std::cout << "Save starts here" << std::endl;
    std::cout << JSON.dump(2) << std::endl;
    std::cout << "Save ends here" << std::endl;

    std::ofstream file("save_state.json");
    file << JSON.dump(2);
}

nlohmann::json SaverLoader::load() {
    std::cout << "Load game" << std::endl;
    std::ifstream file("save_state.json");
    nlohmann::json JSON;
    file >> JSON;
    std::cout << JSON.dump(2) << std::endl;
    return JSON;
}

nlohmann::json SaverLoader::loadConfig() {
    try {
        std::cout << "Load configuration" << std::endl;
        std::ifstream file("conf.json");
        nlohmann::json JSON;
        file >> JSON;
        std::cout << JSON.dump(2) << std::endl;
        return JSON;
    } catch (const std::exception& e) {
        std::cerr << "Error with configuration: " << e.what() << std::endl;
        return nlohmann::json();
    }
} */