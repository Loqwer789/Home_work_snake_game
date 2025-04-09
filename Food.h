
#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"

class Food {
public:
    int x, y;
    
    Food(int width, int height); // ����������� � �����������
    void Generate(Snake& snake);
    bool IsAt(int x, int y) const;
    int GetX() const;
    int GetY() const;

private:
    const int WIDTH;  // ������ �������� ����
    const int HEIGHT; // ������ �������� ����
};

#endif
