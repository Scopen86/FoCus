#pragma once
#include <vector>

#include "Entity.hpp"

class Logic {
    public:
        Logic() {};
        bool checkCollision(Entity& frame, Entity& target);
        void calculateScore(Entity& frame, Entity& target);

        double getScore() const { return score; }
    private:
        double score = 0.0;
};