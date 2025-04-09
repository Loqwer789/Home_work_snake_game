#include "Snake.h"

Snake::Snake(int startX, int startY) : dir(STOP), hasGrown(false) {
    body.push_back({startX, startY});
}

void Snake::Move(Direction newDir) {
    if (dir == STOP) dir = newDir;
    else {
        // Запрет движения в противоположном направлении
        if ((dir == LEFT && newDir == RIGHT) ||
            (dir == RIGHT && newDir == LEFT) ||
            (dir == UP && newDir == DOWN) ||
            (dir == DOWN && newDir == UP)) return;
        dir = newDir;
    }

    // Сохраняем предыдущую позицию головы
    auto newHead = body.front();
    
    switch (dir) {
        case LEFT:  newHead.first--; break;
        case RIGHT: newHead.first++; break;
        case UP:    newHead.second--; break;
        case DOWN:  newHead.second++; break;
    }

    // Добавляем новую голову
    body.insert(body.begin(), newHead);
    
    // Если змейка не выросла, удаляем хвост
    if (!hasGrown) {
        body.pop_back();
    }
    hasGrown = false;
}

void Snake::Grow() {
    hasGrown = true;
}

bool Snake::CheckCollision(int width, int height) const {
    const auto& head = body.front();
    
    // Проверка столкновения со стенами
    if (head.first < 0 || head.first >= width ||
        head.second < 0 || head.second >= height) {
        return true;
    }
    
    // Проверка столкновения с телом
    for (int i = 1; i < body.size(); ++i) {
        if (head == body[i]) {
            return true;
        }
    }
    
    return false;
}

bool Snake::IsAt(int x, int y) const {
    for (const auto& segment : body) {
        if (segment.first == x && segment.second == y) {
            return true;
        }
    }
    return false;
}

int Snake::GetHeadX() const { return body.front().first; }
int Snake::GetHeadY() const { return body.front().second; }
const std::vector<std::pair<int, int>>& Snake::GetBody() const { return body; }
