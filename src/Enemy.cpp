
#include "Enemy.hpp"
Enemy::Enemy(double speed, int fullhp)
    : speed(speed), fullhp(fullhp), pos(0, 0), hp(fullhp), toDirection(0),
      onRoad(0), toFinish(0) {}

void Enemy::move(int x, int y) {
  pos.addx(x * speed);
  pos.addy(y * speed);
  toFinish -= (std::abs(x) + std::abs(y));
}

void Enemy::getHit(int dmg) { hp -= dmg; }
