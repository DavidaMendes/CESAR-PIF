#include "render.h"
#include "game.h"
#include "screen.h"
#include <stdio.h>

void draw_game() {
    screenClear();
    for (int i = 0; i < WIDTH + 2; i++) {
		printf("\033[41m#\033[0m");
	}
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

    for (int i = 0; i < WIDTH + 2; i++) {
		printf("\033[41m#\033[0m");
	}
    printf("\n");
    printf("Pontuação: %d   Recorde: %d\n", pontuacao_atual, recorde);
}
