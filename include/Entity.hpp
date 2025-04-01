//TODO: Implement destructor to free texture memory, Implement sprite sheet animation?
#pragma once
#include <SDL.h>

#include "Vector2f.hpp"
#include "defs.hpp"

class Entity {
    public:
        Entity(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size, float p_vel)
        :tex(p_tex), pos(p_pos), size(p_size), fallVel(p_vel) {};
        Entity(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size)
        :tex(p_tex), pos(p_pos), size(p_size), fallVel(DEFAULT_FALL_VELOCITY) {};
        Entity(SDL_Texture* p_tex, Vector2f p_pos)
        :tex(p_tex), pos(p_pos), size(DEFAULT_SIZE), fallVel(DEFAULT_FALL_VELOCITY) {};
        Entity()
        :tex(nullptr), pos(0, 0), size(DEFAULT_SIZE), fallVel(DEFAULT_FALL_VELOCITY) {};

        ~Entity() {
            SDL_DestroyTexture(tex);
        };

        SDL_Texture* getTex() const { return tex; }
        Vector2f getPosition() const { return pos; }
        Vector2f getSize() const { return size; }
        float getVelocity() const { return fallVel; }

        void update(float deltaTime) {
            pos.y = pos.y + (fallVel * deltaTime);
        }
        
    private:
        SDL_Texture* tex;
        Vector2f pos;
        Vector2f size;
        const float fallVel;
};