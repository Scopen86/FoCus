#pragma once
#include <vector>

#include "Entity.hpp"
#include "Player.hpp"
class Logic {
    public:
        Logic() {};
        void handlePlayerMovement(Player& player, float deltaTime);
        bool checkCollision(Player& player, std::vector<Entity>& enemies);
};