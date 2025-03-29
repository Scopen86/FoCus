#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Player.hpp"

void Player::knockback() {
    srand(time(0));
    int ran = rand() % 50 + 50; // 50 -> 100
    Vector2f delta(ran, ran);
    this->pos = this->pos + delta;
}