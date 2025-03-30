#pragma once
#include <SDL.h>

#include "Entity.hpp"

class Enemy : public Entity {
    public:
        Enemy(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size, Vector2f p_velocity, float p_timing)
        :Entity(p_tex, p_pos, p_size, p_velocity), timing(p_timing) {};

        float getTiming() const { return timing; }

    private:
        float timing; // Spawn timing
};

class squareEnemy : public Enemy {
    public:
        squareEnemy(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size, Vector2f p_velocity, float p_timing)
        :Enemy(p_tex, p_pos, p_size, p_velocity, p_timing) {};
};

class lineEnemy : public Enemy {
    public:
        lineEnemy(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size, Vector2f p_velocity, float p_timing)
        :Enemy(p_tex, p_pos, p_size, p_velocity, p_timing) {};

    private:
        int direction; // 0 = left, 1 = right, 2 = up, 3 = down
};

class bomb : public Enemy {
    public:
        bomb(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size, Vector2f p_velocity, float p_timing)
        :Enemy(p_tex, p_pos, p_size, p_velocity, p_timing) {};

        void update(float deltaTime) {
            pos = pos + (velocity * deltaTime);
        }

        void flash(float flash_timing) {};
        void explode(float explosion_timing) {};
    
    private:
        float flash_timing, explosion_timing;
        bool isFlashing = false;
        bool isExploding = false;
};