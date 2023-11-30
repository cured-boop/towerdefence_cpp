#include "Level.hpp"
#include "Constants.hpp"
Level::Level(const std::vector<std::vector<int>>& _layout, int _width, int _height)
    : layout(_layout), width(_width), height(_height) {
    findRoad();
}

const std::vector<std::vector<int>>& Level::getLayout() const {
    return layout;
}

const std::vector<Pos>& Level::getRoad() const {
    return road;
}

bool Level::pointOnRoad(const Pos& cursor) const {
    auto it = std::find_if(road.begin(), road.end(), [&cursor](const Pos& spot) {
        return cursor.x > (spot.x - 1) * tileWidth &&
               cursor.x < spot.x * tileWidth &&
               cursor.y > (spot.y - 1) * tileHeight &&
               cursor.y < spot.y * tileHeight;
    });

    return it == road.end();
}

bool Level::oob(const Pos& cursor) const {
    return cursor.x < 0 || cursor.x > width || cursor.y < 0 || cursor.y > height;
}

void Level::findRoad() {
    int end = 1;
    road.clear();

    for (int index = 0; index < layout.size(); ++index) {
        const auto& row = layout[index];
        std::vector<Pos> spot;
        for (int i = 0; i < row.size(); ++i) {
            if (row[i] == 1) {
                spot.push_back(Pos(i + 1, index + 1));
            }
        }

        if (!spot.empty()) {
            if (spot[0].x == end) {
                road.insert(road.end(), spot.begin(), spot.end());
            } else {
                road.insert(road.end(), spot.rbegin(), spot.rend());
            }
            end = spot.back().x;
        }
    }
}