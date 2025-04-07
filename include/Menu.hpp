#pragma once
#include <SDL.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

class Menu {
public:
    Menu(RenderWindow& p_window);
    ~Menu();
    
    void showMenu();
    void showInstructions();
    void showCredits();
    void showGameOver();
    
    int getState() const { return state; }
    void isHovering(Entity& button);
    void setState(int p_state) { state = p_state; }
    
private:
    void loadEntity();
    
    int state;
    RenderWindow& window;
    
    Entity title;
    Entity playButton;
    Entity instructionsButton;
    Entity creditsButton;
    Entity restartButton;
    Entity instructions;
    Entity credits;
    Entity gameOver;
};