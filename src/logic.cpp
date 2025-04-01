#include "Logic.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Vector2f.hpp"

// void Logic::handlePlayerMovement(Player& player, float deltaTime) {
//     Vector2f deltaVelocity(0, 0);
//     const Uint8* state = SDL_GetKeyboardState(NULL);
//     float speed = 400.0f;
    
//     if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
//         deltaVelocity.y -= speed;
//     }
//     if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
//         deltaVelocity.y += speed;
//     }
//     if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
//         deltaVelocity.x -= speed;
//     }
//     if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
//         deltaVelocity.x += speed;
//     }
//     player.setVelocity(deltaVelocity);
//     player.update(deltaTime);

//     // Prevent player from going off screen
//     Vector2f playerPos = player.getPosition();
//     if(playerPos.x < 0) player.setPos(Vector2f(0, playerPos.y));
//     if(playerPos.y < 0) player.setPos(Vector2f(playerPos.x, 0));
//     if(playerPos.x + player.getSize().x > SCREEN_WIDTH) {
//         player.setPos(Vector2f(SCREEN_WIDTH - player.getSize().x, playerPos.y));
//     }
//     if(playerPos.y + player.getSize().y > SCREEN_HEIGHT) {
//         player.setPos(Vector2f(playerPos.x, SCREEN_HEIGHT - player.getSize().y));
//     }
// }

bool Logic::checkCollision(Entity& frame, std::vector<Entity&> targets) {
    Vector2f framePos = frame.getPosition();
    for(Entity& target : targets) {
        Vector2f targetPos = target.getPosition();
        if(framePos.x < targetPos.x + target.getSize().x &&
            framePos.x + frame.getSize().x > targetPos.x &&
            framePos.y < targetPos.y + target.getSize().y &&
            framePos.y + frame.getSize().y > targetPos.y) 
        {
            std::cout << "Collision detected!" << std::endl;
            return true;
        }
    }

    return false;
}