#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility> // для std::pair

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Snake {
public:
    Snake(int startX, int startY);
    
    void Move(Direction dir);
    void Grow();
    bool CheckCollision(int width, int height) const;
    bool IsAt(int x, int y) const;
    
    int GetHeadX() const;
    int GetHeadY() const;
    const std::vector<std::pair<int, int>>& GetBody() const;

private:
    std::vector<std::pair<int, int>> body;
    Direction dir;
    bool hasGrown;
};

#endif
