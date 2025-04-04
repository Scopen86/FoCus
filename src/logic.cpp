#include "Logic.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Vector2f.hpp"
#include <iostream>

Logic::Logic() 
    :score(0.0) {
    frameActive = std::vector<bool>(4, false);
    
    keyScanCodes = {
        SDL_SCANCODE_D,
        SDL_SCANCODE_F,
        SDL_SCANCODE_J,
        SDL_SCANCODE_K
    };
}

bool Logic::checkCollision(Entity& frame, Entity& target) {
    Vector2f framePos = frame.getPosition();
    Vector2f targetPos = target.getPosition();

    if(framePos.x < targetPos.x + target.getSize().x &&
        framePos.x + frame.getSize().x > targetPos.x &&
        framePos.y < targetPos.y + target.getSize().y &&
        framePos.y + frame.getSize().y > targetPos.y) 
    {
        std::cout << "Hit!" << std::endl;
        return true;
    }

    std::cout << "Miss!" << std::endl;
    return false;
}

void Logic::calculateScore(Entity& frame, Entity& target) {
    Vector2f frameCenter = frame.getPosition() + frame.getSize() / 2.0f;
    Vector2f targetCenter = target.getPosition() + target.getSize() / 2.0f;
    float distance = frameCenter.getDistance(targetCenter);

    if(distance < 50.0f) {
        score += 100.0f - (distance / 50.0f) * 100.0f;
        std::cout << "Score increased by: " << (100.0f - (distance / 50.0f) * 100.0f) << std::endl;
        std::cout << "Total score: " << score << std::endl;
    } else {
        std::cout << "Too far for points" << std::endl;
    }
}

void Logic::handleMovement(std::vector<Entity>& frames, std::vector<Entity>& targets, float currentTime) {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    
    for(int i = 0; i < 4; i++) {
        if(keyState[keyScanCodes[i]]) {
            frameActive[i] = true;
            
            for(Entity& target : targets) {
                if(currentTime >= target.getTiming() && target.getPosition().y >= 0) {
                    if(checkCollision(frames[i], target)) {
                        calculateScore(frames[i], target);
                        target.moveOutOfScreen();
                    }
                }
            }
        }
    }
}

void Logic::processKeyEvent(const SDL_Event& event) {
    if(event.type == SDL_KEYUP) {
        SDL_Keycode keycode = event.key.keysym.sym;
        
        if(keycode == SDLK_d) frameActive[0] = false;
        else if(keycode == SDLK_f) frameActive[1] = false; 
        else if(keycode == SDLK_j) frameActive[2] = false;
        else if(keycode == SDLK_k) frameActive[3] = false;
    }
}

bool Logic::isFrameActive(int frameIndex) const {
    if(frameIndex >= 0 && frameIndex < static_cast<int>(frameActive.size())) {
        return frameActive[frameIndex];
    }
    return false;
}