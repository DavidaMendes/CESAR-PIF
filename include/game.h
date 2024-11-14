#ifndef GAME_H
#define GAME_H

#define WIDTH 40
#define HEIGHT 20
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

extern Snake snake;
extern Game game;
extern int pontuacao_atual;
extern int recorde;

void init_game();

#endif
