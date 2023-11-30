/*
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "Pos.hpp"
#include "Constants.hpp"
#include "SaverLoader.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include "State.hpp"
#include "Wave.hpp"
#include "Level.hpp"

class Game {
private:
    SaverLoader reader;
    // Declare other member variables as needed

public:
    Game() {
        // Implement the constructor
    }

    std::tuple<int, int, int, int, std::vector<Json::Value>, std::vector<std::vector<int>>> loadConfig() {
        // Implement the loadConfig method
    }

    bool loadGame() {
        try {
            Json::Value JSON = reader.load();
            overall.loadStatus(JSON);
            wave.load(JSON["wave"].asInt());
            std::vector<Json::Value> towerList = JSON["towers"].asVector();
            towersBuffer.clear();
            for (const auto& tower : towerList) {
                std::string Type = tower["type"].asString();
                std::map<std::string, int> posMap;
                for (const auto& entry : tower["pos"].getMemberNames()) {
                    posMap[entry] = tower["pos"][entry].asInt();
                }

                Tower* newTower = nullptr;
                if (Type == "1") newTower = towers.wrap(1, new Pos(posMap["x"], posMap["y"])); //no functionality for this right now
                else if (Type == "2") newTower = towers.wrap(2, new Pos(posMap["x"], posMap["y"]));
                else if (Type == "3") newTower = towers.wrap(3, new Pos(posMap["x"], posMap["y"]));
                else if (Type == "4") newTower = towers.wrap(4, new Pos(posMap["x"], posMap["y"]));
                else if (Type == "5") newTower = towers.wrap(5, new Pos(posMap["x"], posMap["y"]));

                if (newTower) {
                    towersBuffer.push_back(newTower);
                }
            }

            std::cout << "Towers loaded" << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    void onTick() {
        // Implement the onTick method
    }

    void save() {
        reader.save();
    }

    void start() {
        enemiesBuffer = wave.enemies();
        engage();
        std::cout << "Start Game" << std::endl;
    }

    // Implement other methods as needed
};

// Implement the remaining methods as necessary

int main() {
    // Implement the main function if needed
    return 0;
}

*/