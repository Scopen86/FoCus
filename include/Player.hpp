#pragma once
#include "Entity.hpp"

class Player : public Entity {
    public:
        Player(SDL_Texture* p_tex, Vector2f p_pos, int p_hp)
        :Entity(p_tex, p_pos, Vector2f(32, 32)), hp(3) {};
        
        void knockback();
        void hit() {
            knockback();
            hp -= 1;
            if(hp < 0) hp = 0;
        }

        int getHp() const { return hp; }
    private:
        int hp;
};