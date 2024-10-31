#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define WIDTH 20
#define HEIGHT 10
#define INITIAL_LENGTH 3

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[WIDTH * HEIGHT];
    int length;
    char direction;
} Snake;

typedef struct {
    Point food;
} Game;

int x = 0, y = 0;
int incX = 1, incY = 0;
Snake snake;
Game game;

void init_game() {
    snake.length = INITIAL_LENGTH;
    snake.direction = 'R';
    for (int i = 0; i < INITIAL_LENGTH; i++) {
        snake.body[i].x = INITIAL_LENGTH - i - 1;
        snake.body[i].y = 0;
    }
    game.food.x = rand() % WIDTH;
    game.food.y = rand() % HEIGHT;
}

void draw_game() {
    screenClear();
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int is_snake = 0;
            for (int j = 0; j < snake.length; j++) {
                if (snake.body[j].x == x && snake.body[j].y == y) {
                    is_snake = 1;
                    break;
                }
            }
            if (is_snake) {
                printf("O");
            } else if (game.food.x == x && game.food.y == y) {
                printf("F");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
}

void update_snake() {
    Point new_head = snake.body[0];
    switch (snake.direction) {
        case 'U': new_head.y--; break;
        case 'D': new_head.y++; break;
        case 'L': new_head.x--; break;
        case 'R': new_head.x++; break;
    }

    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    snake.body[0] = new_head;

    if (new_head.x == game.food.x && new_head.y == game.food.y) {
        snake.length++;
        game.food.x = rand() % WIDTH;
        game.food.y = rand() % HEIGHT;
    }
}

void change_direction(int ch) {
    if (ch == 'w' && snake.direction != 'D') snake.direction = 'U';
    if (ch == 's' && snake.direction != 'U') snake.direction = 'D';
    if (ch == 'a' && snake.direction != 'R') snake.direction = 'L';
    if (ch == 'd' && snake.direction != 'L') snake.direction = 'R';
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    printHello(x, y);
    screenUpdate();

    while (ch != 10) { // 10 é o código do Enter
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            int newX = x + incX;
            if (newX >= (MAXX -strlen("Hello World") -1) || newX <= MINX+1) incX = -incX;
            int newY = y + incY;
            if (newY >= MAXY-1 || newY <= MINY+1) incY = -incY;

            printKey(ch);
            printHello(newX, newY);

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
