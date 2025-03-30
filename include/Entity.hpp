//TODO: Implement destructor to free texture memory, Implement sprite sheet animation?
#pragma once
#include <SDL.h>

#include "Vector2f.hpp"
#include "defs.hpp"

class Entity {
    public:
        Entity(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size, Vector2f p_velocity)
        :tex(p_tex), pos(p_pos), size(p_size), velocity(p_velocity) {};
        Entity(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size)
        :tex(p_tex), pos(p_pos), size(p_size), velocity(0, 0) {};
        Entity(SDL_Texture* p_tex, Vector2f p_pos)
        :tex(p_tex), pos(p_pos), size(Vector2f(32, 32)), velocity(0, 0) {};

        ~Entity() {}; //Implement this later

        SDL_Texture* getTex() const { return tex; }
        Vector2f getPosition() const { return pos; }
        Vector2f getSize() const { return size; }
        
        Vector2f getVelocity() const { return velocity; }
        void setVelocity(Vector2f vel) { velocity = vel; }

        void update(float deltaTime) {
            pos = pos + (velocity * deltaTime);
        }

        void setPos(Vector2f newPos) { pos = newPos; }
        
    protected:
        SDL_Texture* tex;
        Vector2f pos;
        Vector2f size;
        Vector2f velocity;
};