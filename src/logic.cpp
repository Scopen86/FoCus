#include "Logic.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Vector2f.hpp"
#include <iostream>

Logic::Logic() : score(0.0), frame0Active(false), frame1Active(false), 
                frame2Active(false), frame3Active(false) {}

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

void Logic::handleKeyboardInput(Entity& frame0, Entity& frame1, Entity& frame2, Entity& frame3, std::vector<Entity>& targets, float currentTime) {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    // Check all keys every frame
    if(keyState[SDL_SCANCODE_D]) {
        frame0Active = true;
        for(Entity& target : targets) {
            if(currentTime >= target.getTiming()) {
                if(checkCollision(frame0, target)) {
                    calculateScore(frame0, target);
                    target.moveOutOfScreen();
                }
            }
        }
    }

    if(keyState[SDL_SCANCODE_F]) {
        frame1Active = true;
        for(Entity& target : targets) {
            if(currentTime >= target.getTiming()) {
                if(checkCollision(frame1, target)) {
                    calculateScore(frame1, target);
                    target.moveOutOfScreen();
                }
            }
        }
    }

    if(keyState[SDL_SCANCODE_J]) {
        frame2Active = true;
        for(Entity& target : targets) {
            if(currentTime >= target.getTiming()) {
                if(checkCollision(frame2, target)) {
                    calculateScore(frame2, target);
                    target.moveOutOfScreen();
                }
            }
        }
    }

    if(keyState[SDL_SCANCODE_K]) {
        frame3Active = true;
        for(Entity& target : targets) {
            if(currentTime >= target.getTiming()) {
                if(checkCollision(frame3, target)) {
                    calculateScore(frame3, target);
                    target.moveOutOfScreen();
                }
            }
        }
    }
}