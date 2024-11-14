#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define WIDTH 40
#define HEIGHT 20
#define INITIAL_LENGTH 3
#define HIGHSCORE_FILE "highscore.txt"

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
int recorde = 0;
int pontuacao_atual = 0;

void init_game() {
    snake.length = INITIAL_LENGTH;
    snake.direction = 'R';
    pontuacao_atual = 0;
    for (int i = 0; i < INITIAL_LENGTH; i++) {
        snake.body[i].x = INITIAL_LENGTH - i - 1;
        snake.body[i].y = 0;
    }
    game.food.x = rand() % WIDTH;
    game.food.y = rand() % HEIGHT;
}

void draw_game() {
    screenClear();
    for (int i = 0; i < WIDTH + 2; i++) printf("\033[41m#\033[0m");
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
                printf("\033[42mO\033[0m");
            } else if (game.food.x == x && game.food.y == y) {
                printf("\033[43mÓ\033[0m");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("\033[41m#\033[0m");
    printf("\n");
    printf("Pontuação: %d   Recorde: %d\n", pontuacao_atual, recorde);
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
        pontuacao_atual++;
        game.food.x = rand() % WIDTH;
        game.food.y = rand() % HEIGHT;
    }
}

int check_collision() {
    Point head = snake.body[0];
    
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[i].x == head.x && snake.body[i].y == head.y) {
            return 1;
        }
    }
    
    if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT) {
        return 1;
    }
    
    return 0;
}

void change_direction(int ch) {
    if (ch == 'w' && snake.direction != 'D') snake.direction = 'U';
    if (ch == 's' && snake.direction != 'U') snake.direction = 'D';
    if (ch == 'a' && snake.direction != 'R') snake.direction = 'L';
    if (ch == 'd' && snake.direction != 'L') snake.direction = 'R';
}

void load_highscore() {
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    if (file) {
        fscanf(file, "%d", &recorde);
        fclose(file);
    }
}

void save_highscore() {
    if (pontuacao_atual > recorde) {
        recorde = pontuacao_atual;
        FILE *file = fopen(HIGHSCORE_FILE, "w");
        if (file) {
            fprintf(file, "%d", recorde);
            fclose(file);
        }
    }
}

int main() {
    int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(100);

    load_highscore();
    init_game();
    draw_game();

    while (ch != 10) {
        if (keyhit()) {
            ch = readch();
            change_direction(ch);
        }

        if (timerTimeOver() == 1) {
            update_snake();

            if (check_collision()) {
                printf("Game Over! A cobra se colidiu com ela mesma.\n");
                break;
            }

            draw_game();
        }
    }

    save_highscore();

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
