#pragma once
#include <SDL.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

class Menu {
public:
    Menu(RenderWindow& p_window);
    ~Menu();
    
    void showMenu();
    void showInfo();
    void showGameOver();
    
    int getState() const { return state; }
    void isHovering(Entity& button);
    void setState(int p_state) { state = p_state; }
    void setFinalScore(float score) { finalScore = score; }
    void setMaxCombo(int combo) { finalMaxCombo = combo; }
    
private:
    void loadEntity();
    
    int state;
    RenderWindow& window;
    float finalScore = 0.0f;
    int finalMaxCombo = 0;
    
    Entity title;
    Entity playButton;
    Entity infoButton;

    Entity info;
    Entity gameOver;

    Entity restartButton;
    Entity homeButton;
};