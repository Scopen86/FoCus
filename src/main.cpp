#include "Game.hpp"
#include "Menu.hpp"

int main(int argc, char* argv[]) {
    Game game;
    
    if (!game.init()) {
        return 1;
    }

    Menu menu(game.getWindow());
    bool running = true;
    
    while (running) {
        switch (menu.getState()) {
            case 0:
                running = false;
                break;
            case 1:
                menu.showMenu();
                break;
            case 2:
                menu.showInfo();
                break;
            case 4:
                game.reset();
                if(!game.run()) {
                    if(game.didUserQuit()) {
                        running = false;
                    } else {
                        menu.setFinalScore(game.getScore());
                        menu.setMaxCombo(game.getMaxCombo());
                        menu.setState(5);
                    }
                }
                break;
            case 5:
                menu.showGameOver();
                break;
            default:
                std::cout << "Invalid menu state" << std::endl;
                running = false;
                break;
        }
    }
    
    return 0;
}