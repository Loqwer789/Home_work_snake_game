#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include <ncurses.h>

class Game {
public:
    Game(int width = 70, int height = 35);
    void Run();
	//Размеры поля можно менять
private:
    void Setup();
    void Draw() const;
    void Input();
    void Logic();
    void ShowWelcomeMessage() const;

    const int WIDTH;
    const int HEIGHT;
    bool gameOver;
    int score;
    Snake snake;
    Food food;
    Direction dir;
};

#endif
