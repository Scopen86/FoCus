#pragma once
#include <vector>

#include "Enemy.hpp"
#include "Player.hpp"

class Logic {
    public:
        Logic() {};
        void handlePlayerMovement(Player& player, float deltaTime);
        bool checkCollision(Player& player, std::vector<Enemy>& enemies);
};