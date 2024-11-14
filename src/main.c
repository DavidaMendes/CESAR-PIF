#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "snake.h"
#include "render.h"
#include "highscore.h"

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
				screenClear();
                printf("Game Over! A cobra colidiu.\n");
				printf("Pressione qualquer tecla para sair.\n");
				getchar();
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
