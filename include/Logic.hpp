#pragma once
#include <vector>

#include "Entity.hpp"

class Logic {
    public:
        Logic() {};
        bool checkCollision(Entity& frame, std::vector<Entity&> targets);
};