#pragma once
#include "Entity.hpp"
#include "defs.hpp"
class Player : public Entity {
    public:
        Player(SDL_Texture* p_tex, Vector2f p_pos, int p_hp)
        :Entity(p_tex, p_pos, Vector2f(DEFAULT_SIZE)), hp(p_hp) {};
        
        void knockback();
        void hit();

        int getHp() const { return hp; }
    private:
        int hp;
};