/*#include <Tower.hpp>
#include <algorithm>
#include <cmath>
Tower::Tower(int dmg, int range, int cost, std::string Type, Pos pos, Game*
game) : dmg(dmg), range(range), cost(cost), Type(Type), pos(pos), game(game) {}

std::vector<Enemy> Tower::withinRange(std::vector<Enemy>& enemies) {
    std::vector<Enemy> result;
    for (auto& enemy : enemies) {
        double distance = std::sqrt(std::pow(pos.x - enemy.pos.x, 2) +
std::pow(pos.y - enemy.pos.y, 2)); if (distance < range) {
            result.push_back(enemy);
        }
    }
    std::sort(result.begin(), result.end(), [](const Enemy& a, const Enemy& b) {
return a.toFinish < b.toFinish; }); return result;
}

void Tower::attack(int time) {
    if (cooldown(time)) {
        auto enemiesInRange = withinRange(game->enemiesBuffer);
        if (!enemiesInRange.empty()) {
            enemiesInRange.front().getHit(dmg);
        }
    }
}

bool Tower::cooldown(int time) {
    return time % static_cast<int>(100.0 / (1.0 * 100)) < 1;
}

mainInfo::mainInfo(int dmg, int range, int cost) : dmg(dmg), range(range),
cost(cost) {}

towersToSaveState::towersToSaveState(Game* game, std::vector<Json::Value>
JSONtower) : game(game) { for (size_t i = 0; i < JSONtower.size(); ++i) { auto
towerInfo = JSONtower[i]; int dm = towerInfo["dmg"].asInt(); int rang =
towerInfo["range"].asInt(); int cos = towerInfo["cost"].asInt(); Alltowers[i +
1] = mainInfo(dm, rang, cos);
    }
}
*/