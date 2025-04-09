#include "Game.h"
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <cstring>
//#include <locale.h>


void Game::ShowWelcomeMessage() const {
clear();  
attron(A_BOLD | COLOR_PAIR(3));

const char* lines[] = {
	" MIPT SNAKE GAME",
	"1946 - 2025",
	"===========",
	"use WASD or use strelochki ",
	"                         ",
	"                         ",
	"             ",
	"        use X for exit         ",
	"created be Serzhanov Aleksey B01-301"
};


int start_y = HEIGHT/2 - 3;

for(int i = 0; i < sizeof(lines)/sizeof(lines[0]); i++){
	int x = (WIDTH - strlen(lines[i])) / 2;
	mvprintw(start_y + i, x, "%s", lines[i]);
	}

attron(COLOR_PAIR(3) | A_BLINK);

const char* pressMsg = "Press any knopka for start";

int x = (WIDTH - strlen(pressMsg)) / 2;
mvprintw(HEIGHT - 4, x, "%ls", pressMsg);
attroff(COLOR_PAIR(3));
attroff(A_BLINK);


//mvprintw(y, x, "%s", msg);
//attroff(A_BOLD | COLOR_PAIR(3));

refresh();

timeout(3000);
getch();
timeout(100);

}


Game::Game(int width, int height) 
    : WIDTH(width), 
      HEIGHT(height),
      gameOver(false),
      score(0),
      snake(width/2, height/2),
      food(width, height),
      dir(STOP) {}

void Game::Setup() {
//setlocale(LC_ALL, "");    
initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);
    
    // Инициализация цветов
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Змейка
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Еда
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Границы
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // это для сообщений

    food.Generate(snake);
}

void Game::Draw() const {
    clear();
    
    // Рисуем границы
    attron(COLOR_PAIR(3));
    for (int x = 0; x < WIDTH+2; x++) {
        mvprintw(0, x, "#");
        mvprintw(HEIGHT+1, x, "#");
    }
    for (int y = 1; y < HEIGHT+1; y++) {
        mvprintw(y, 0, "#");
        mvprintw(y, WIDTH+1, "#");
    }
    attroff(COLOR_PAIR(3));
    
    // Рисуем змейку
    attron(COLOR_PAIR(1));
    for (const auto& segment : snake.GetBody()) {
        mvprintw(segment.second + 1, segment.first + 1, "O");
    }
    attroff(COLOR_PAIR(1));
    
    // Рисуем еду
    attron(COLOR_PAIR(2));
    mvprintw(food.GetY() + 1, food.GetX() + 1, "@");
    attroff(COLOR_PAIR(2));
    
    // Вывод счета
    mvprintw(HEIGHT + 2, 0, "Final schet: %d", score);
    refresh();
}

void Game::Input() {
    int ch = getch();
    switch(ch) {
        case 'a': case KEY_LEFT:  dir = LEFT;  break;
        case 'd': case KEY_RIGHT: dir = RIGHT; break;
        case 'w': case KEY_UP:    dir = UP;    break;
        case 's': case KEY_DOWN:  dir = DOWN;  break;
        case 'x': gameOver = true; break;
    }
}

void Game::Logic() {
    snake.Move(dir);
    
    // Проверка на съедение еды
    if (snake.GetHeadX() == food.GetX() && 
        snake.GetHeadY() == food.GetY()) {
        score += 10;
        snake.Grow();
        food.Generate(snake);
    }
    
    // Проверка столкновений
    if (snake.CheckCollision(WIDTH, HEIGHT)) {
        gameOver = true;
    }
}

void Game::Run() {
    Setup();

    ShowWelcomeMessage();
    clear();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    endwin();
    printf("Конец игры, ваш счёт: %d\n", score);
}
