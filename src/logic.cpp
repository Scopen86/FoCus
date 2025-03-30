#include "Logic.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Vector2f.hpp"

void Logic::handlePlayerMovement(Player& player, float deltaTime) {
    Vector2f deltaPos(0, 0);
    const Uint8* state = SDL_GetKeyboardState(NULL);
    float speed = player.getSpeed() * deltaTime; 
    
    if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        deltaPos.y -= speed;
    }
    if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        deltaPos.y += speed;
    }
    if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        deltaPos.x -= speed;
    }
    if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        deltaPos.x += speed;
    }
    player.move(deltaPos);

    // Prevent player from going off screen
    Vector2f playerPos = player.getPosition();
    if(playerPos.x < 0) player.setPos(Vector2f(0, playerPos.y));
    if(playerPos.y < 0) player.setPos(Vector2f(playerPos.x, 0));
    if(playerPos.x + player.getSize().x > SCREEN_WIDTH) {
        player.setPos(Vector2f(SCREEN_WIDTH - player.getSize().x, playerPos.y));
    }
    if(playerPos.y + player.getSize().y > SCREEN_HEIGHT) {
        player.setPos(Vector2f(playerPos.x, SCREEN_HEIGHT - player.getSize().y));
    }
}

bool Logic::checkCollision(Player& player, std::vector<Entity>& enemies) {
    Vector2f playerPos = player.getPosition();
    for(Entity& enemy : enemies) {
        Vector2f enemyPos = enemy.getPosition();
        if(playerPos.x < enemyPos.x + enemy.getSize().x &&
            playerPos.x + player.getSize().x > enemyPos.x &&
            playerPos.y < enemyPos.y + enemy.getSize().y &&
            playerPos.y + player.getSize().y > enemyPos.y) 
        {
            std::cout << "Collision detected!" << std::endl;
            return true;
        }
    }

    return false;
}