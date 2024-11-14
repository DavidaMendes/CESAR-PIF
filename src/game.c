#include "game.h"
#include <stdlib.h>

Snake snake;
Game game;
int pontuacao_atual = 0;
int recorde = 0;

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
