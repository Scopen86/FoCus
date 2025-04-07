#include <iostream>
#include <SDL.h>

#include "Menu.hpp"
#include "defs.hpp"
#include "Game.hpp"

Menu::Menu(RenderWindow& p_window)
    :state(1), window(p_window),
    title(window.loadTexture("./res/textures/menu/title.png"), Vector2f((SCREEN_WIDTH - DEFAULT_LONG_SIZE.x) / 2, 50), DEFAULT_LONG_SIZE),
    playButton(window.loadTexture("./res/textures/menu/play_button.png"), Vector2f((SCREEN_WIDTH - DEFAULT_SIZE.x * 2) / 2, 250), DEFAULT_SIZE * 2),
    infoButton(window.loadTexture("./res/textures/menu/info_button.png"), Vector2f((SCREEN_WIDTH - DEFAULT_SIZE.x * 2) / 2, 500), DEFAULT_SIZE * 2),
    restartButton(window.loadTexture("./res/textures/menu/restart_button.png"), Vector2f((SCREEN_WIDTH - DEFAULT_SIZE.x * 2) / 2, 500), DEFAULT_SIZE * 2),

    info(window.loadTexture("./res/textures/menu/info.png"), Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)),
    
    gameOver(window.loadTexture("./res/textures/menu/game_over.png"), Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)) {
}

Menu::~Menu() {
    SDL_DestroyTexture(title.getTex());
    SDL_DestroyTexture(playButton.getTex());
    SDL_DestroyTexture(infoButton.getTex());

    SDL_DestroyTexture(info.getTex());
    SDL_DestroyTexture(gameOver.getTex());
    SDL_DestroyTexture(restartButton.getTex());
}

// Menu::isHovering(Entity& button) {
//     int mouseX, mouseY;
//     SDL_GetMouseState(&mouseX, &mouseY); 
//     if (mouseX >= button.getPosition().x && mouseX <= button.getPosition().x + button.getSize().x &&
//         mouseY >= button.getPosition().y && mouseY <= button.getPosition().y + button.getSize().y) {
//         // Change texture to indicate hover
//         button.setTex(window.loadTexture("./res/textures/menu/hover_button.png"));
//     } else {
//         // Reset to original texture
//         button.setTex(window.loadTexture("./res/textures/menu/play_button.png"));
//     }
// }

void Menu::showMenu() {
    bool quit = false;
    SDL_Event event;
    
    while (!quit) {
        window.clear();
        
        window.draw(title);
        window.draw(playButton);
        window.draw(infoButton);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state = 0; // Quit state
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                
                if (mouseX >= playButton.getPosition().x && mouseX <= playButton.getPosition().x + playButton.getSize().x &&
                    mouseY >= playButton.getPosition().y && mouseY <= playButton.getPosition().y + playButton.getSize().y) {
                    state = 4; // Start game
                    quit = true;
                }
                else if (mouseX >= infoButton.getPosition().x && mouseX <= infoButton.getPosition().x + infoButton.getSize().x &&
                         mouseY >= infoButton.getPosition().y && mouseY <= infoButton.getPosition().y + infoButton.getSize().y) {
                    state = 2; // Show info
                    quit = true;
                }
                else if (mouseX >= restartButton.getPosition().x && mouseX <= restartButton.getPosition().x + restartButton.getSize().x &&
                         mouseY >= restartButton.getPosition().y && mouseY <= restartButton.getPosition().y + restartButton.getSize().y) {
                    state = 0; // Quit
                    quit = true;
                }
            }
        }
        
        window.display();
    }
}

void Menu::showInfo() {
    bool quit = false;
    SDL_Event event;
    
    while (!quit) {
        window.clear();
        
        window.draw(info);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state = 0; // Quit state
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                state = 1; // Return to menu
                quit = true;
            }
        }
        
        window.display();
    }
}


void Menu::showGameOver() {
    bool quit = false;
    SDL_Event event;
    
    while (!quit) {
        window.clear();
        
        window.draw(gameOver);
        
        window.drawText("Game Over", Vector2f(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100), WHITE, 48);
        window.drawText("Press any key to continue", Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100), WHITE, 24);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state = 0; // Quit state
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                state = 1; // Return to menu
                quit = true;
            }
        }
        
        window.display();
    }
}