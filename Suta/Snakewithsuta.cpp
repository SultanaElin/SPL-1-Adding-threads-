#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

struct Snake {
    int x, y;
};

vector<Snake> snake;
int direction;
bool gameover;

HANDLE hConsole;

void drawSnake() {
    COORD coord;
    coord.X = snake[0].x;
    coord.Y = snake[0].y;
    SetConsoleCursorPosition(hConsole, coord);
    cout << "O";

    for (int i = 1; i < snake.size(); ++i) {
        coord.X = snake[i].x;
        coord.Y = snake[i].y;
        SetConsoleCursorPosition(hConsole, coord);
        cout << "o";
    }
}

void drawFood(int foodX, int foodY) {
    COORD coord;
    coord.X = foodX;
    coord.Y = foodY;
    SetConsoleCursorPosition(hConsole, coord);
    cout << "*";
}

void generateFood(int &foodX, int &foodY) {
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void updateGame(int &foodX, int &foodY) {
    COORD coord;
    coord.X = snake[snake.size() - 1].x;
    coord.Y = snake[snake.size() - 1].y;
    SetConsoleCursorPosition(hConsole, coord);
    cout << " ";

    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case 0: // UP
            snake[0].y--;
            break;
        case 1: // DOWN
            snake[0].y++;
            break;
        case 2: // LEFT
            snake[0].x--;
            break;
        case 3: // RIGHT
            snake[0].x++;
            break;
    }

    // Check for collision with walls
    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
        gameover = true;
        return;
    }

    // Check for collision with itself
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameover = true;
            return;
        }
    }

    // Check for collision with food
    if (snake[0].x == foodX && snake[0].y == foodY) {
        snake.push_back({foodX, foodY});
        generateFood(foodX, foodY);
    }
}

DWORD WINAPI gameLoop(LPVOID lpParam) {
    int foodX, foodY;
    generateFood(foodX, foodY);

    while (!gameover) {
        drawSnake();
        drawFood(foodX, foodY);
        updateGame(foodX, foodY);
        Sleep(200);
        system("cls");
    }

    return 0;
}

DWORD WINAPI keyboardInput(LPVOID lpParam) {
    while (!gameover) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            direction = 0; // UP
        } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            direction = 1; // DOWN
        } else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            direction = 2; // LEFT
        } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            direction = 3; // RIGHT
        }
    }

    return 0;
}

int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gameover = false;
    direction = 3; // Initial direction: RIGHT

    // Initialize snake
    snake.push_back({WIDTH / 2, HEIGHT / 2});

    HANDLE hGameThread = CreateThread(NULL, 0, gameLoop, NULL, 0, NULL);
    HANDLE hInputThread = CreateThread(NULL, 0, keyboardInput, NULL, 0, NULL);

    WaitForSingleObject(hGameThread, INFINITE);
    WaitForSingleObject(hInputThread, INFINITE);

    CloseHandle(hGameThread);
    CloseHandle(hInputThread);

    return 0;
}
