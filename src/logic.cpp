#include "Logic.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Vector2f.hpp"

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