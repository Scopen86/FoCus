//TODO: Implement destructor to free texture memory, Implement sprite sheet animation?
#pragma once
#include <SDL.h>
#include "Vector2f.hpp"

class Entity {
    public:
        Entity(SDL_Texture* p_tex, Vector2f p_pos, Vector2f p_size)
        :pos(p_pos), tex(p_tex), size(p_size)
        {};
        Entity(SDL_Texture* p_tex, Vector2f p_pos)
        :pos(p_pos), tex(p_tex), size(Vector2f(32, 32))
        {};
        ~Entity() {}; //Implement this later

        SDL_Texture* getTex() const { return tex; }
        Vector2f getPosition() const { return pos; }
        Vector2f getSize() const { return size; }
        float getSpeed() const { return speed; }

        void move(Vector2f delta) { pos = pos + delta; }
        void setPos(Vector2f newPos) { pos = newPos; }
    private:
        Vector2f pos;
        Vector2f size;
        SDL_Texture* tex;
        const float speed = 3.0;
};