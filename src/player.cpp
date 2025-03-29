#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Player.hpp"
#include "Audio.hpp"
void Player::knockback() {
    srand(time(0));
    int ran = rand() % 50 + 50; // 50 -> 100
    Vector2f delta(ran, ran);
    this->pos = this->pos + delta;
}

void Player::hit() {
    this->knockback();

    Audio hitSound;
    hitSound.loadSound("./res/hitHurt.wav");
    hitSound.playSound();

    // No need to use getter and setter for speed, because this is inherited from Entity class
    float tempSpeed = speed; 
    speed = 0.0f;
    SDL_Delay(100);
    speed = tempSpeed;

    hp -= 1;
    if(hp < 0) hp = 0;
}