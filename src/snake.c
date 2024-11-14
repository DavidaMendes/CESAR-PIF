#include "snake.h"
#include "game.h"
#include <stdlib.h>

void update_snake() {
    Point new_head = snake.body[0];
    switch (snake.direction) {
        case 'U':
			new_head.y--;
			break;
        case 'D':
			new_head.y++;
			break;
        case 'L':
			new_head.x--;
			break;
        case 'R':
			new_head.x++;
			break;
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
    if (ch == 'w' && snake.direction != 'D') {
		snake.direction = 'U';
	}
    if (ch == 's' && snake.direction != 'U') {
		snake.direction = 'D';
	}
    if (ch == 'a' && snake.direction != 'R') {
		snake.direction = 'L';
	}
    if (ch == 'd' && snake.direction != 'L') {
		snake.direction = 'R';
	}
}
