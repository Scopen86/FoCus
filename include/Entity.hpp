//TODO: Implement destructor to free texture memory, Implement sprite sheet animation?
#pragma once
#include <SDL.h>

#include "Vector2f.hpp"
#include "defs.hpp"

class Entity {
    public:
        Entity(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size)
        :tex(p_tex), pos(p_pos), size(p_size)
        {};
        Entity(SDL_Texture* p_tex, Vector2f p_pos)
        :tex(p_tex), pos(p_pos), size(DEFAULT_SIZE)
        {};
        ~Entity() {}; //Implement this later

        SDL_Texture* getTex() const { return tex; }
        Vector2f getPosition() const { return pos; }
        Vector2f getSize() const { return size; }
        float getSpeed() const { return speed; }
        void setSpeed(float newSpeed) { speed = newSpeed; }

        void move(Vector2f delta) { pos = pos + delta; }
        void setPos(Vector2f newPos) { pos = newPos; }
    protected:
        SDL_Texture* tex;
        Vector2f pos;
        Vector2f size;
        float speed = 3.0;
};