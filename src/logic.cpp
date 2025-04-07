#include "Logic.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Vector2f.hpp"
#include <iostream>

Logic::Logic() 
    :score(0.0), combo(0), lastHitGrade(-1), perfectCount(0), greatCount(0), goodCount(0), okayCount(0), missCount(0) {
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
    
    if (distance < 10.0f) {
        lastHitGrade = 4;
        perfectCount++;
        score += 100.0f * (1.0f + combo * 0.01f);
        incrementCombo();
    } else if (distance < 25.0f) {
        lastHitGrade = 3;
        greatCount++;
        score += 75.0f * (1.0f + combo * 0.008f);
        incrementCombo();
    } else if (distance < 35.0f) {
        lastHitGrade = 2;
        goodCount++;
        score += 50.0f * (1.0f + combo * 0.005f);
        incrementCombo();
    } else if (distance < 50.0f) {
        lastHitGrade = 1;
        okayCount++;
        score += 25.0f;
        incrementCombo();
    } else {
        lastHitGrade = 0;
        missCount++;
        resetCombo();
    }
}

void Logic::checkMissedTargets(std::vector<Entity>& targets, float currentTime) {
    for(Entity& target : targets) {
        if(currentTime >= target.getTiming() && 
           target.getPosition().y > SCREEN_HEIGHT) {
            
            lastHitGrade = 0; // MISSED
            missCount++;
            resetCombo();
            
            // Move target out of screen to avoid counting it multiple times
            target.moveOutOfScreen();
            
            std::cout << "Target missed!" << std::endl;
        }
    }
}

const std::string Logic::getGradeString() const {
    switch (lastHitGrade) {
        case 4: return "PERFECT";
        case 3: return "GREAT";
        case 2: return "GOOD";
        case 1: return "OKAY";
        case 0: return "MISS";
        case -1: return "";
        default: return "NONE";
    }
}

void Logic::handleInput(std::vector<Entity>& frames, std::vector<Entity>& targets, float currentTime) {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    
    for(int i = 0; i < 4; i++) {
        if(keyState[keyScanCodes[i]]) {
            frameActive[i] = true;
            
            for(Entity& target : targets) {
                if(currentTime >= target.getTiming() && target.getPosition().y >= 0 && target.getPosition().y < SCREEN_HEIGHT) {
                    if(checkCollision(frames[i], target)) {
                        calculateScore(frames[i], target);
                        target.moveOutOfScreen();
                        break; // Only check one time when the key is pressed
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
