#include "highscore.h"
#include "game.h"
#include <stdio.h>

#define HIGHSCORE_FILE "highscore.txt"

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
