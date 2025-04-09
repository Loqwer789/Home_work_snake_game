
#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"

class Food {
public:
    int x, y;
    
    Food(int width, int height); // Конструктор с параметрами
    void Generate(Snake& snake);
    bool IsAt(int x, int y) const;
    int GetX() const;
    int GetY() const;

private:
    const int WIDTH;  // Ширина игрового поля
    const int HEIGHT; // Высота игрового поля
};

#endif
