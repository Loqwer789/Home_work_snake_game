#include "Food.h"
#include "Snake.h"
#include <cstdlib>

Food::Food(int width, int height) : WIDTH(width), HEIGHT(height) {
    // Начальная позиция будет сгенерирована при первом вызове Generate()
}

void Food::Generate(Snake& snake) {
    bool onSnake;
    do {
        onSnake = false;
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
        
        // Проверка, не находится ли еда на змейке
        for (const auto& segment : snake.GetBody()) {
            if (segment.first == x && segment.second == y) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

bool Food::IsAt(int x, int y) const {
    return this->x == x && this->y == y;
}

int Food::GetX() const { return x; }
int Food::GetY() const { return y; }