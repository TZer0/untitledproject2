#include "../port.h"
#include "level.h"
#include "../draw.h"
#include "../game.h"

void cmLevel::init() {
    tiles.resize(30);
    for (int j = 0; j<30; j++) {
        tiles[j].resize(30);
        tiles[j][21] = 1;
    }
    tiles[10][20] = 1;
    tiles[10][19] = 1;
    tiles[10][18] = 1;
}

void cmLevel::level_init() {
}

int cmLevel::load() {
    return 0;
}

void cmLevel::process(double delta) {
}

void cmLevel::draw() {
    int i, k;
    for (k = 0; k<30; k++){
        for (i = 0; i<30; i++){
            if (tiles[k][i] == 1){
            rectfill(mGame->mDraw->buffer, WTOS_X(k*32), WTOS_Y(i*32),WTOS_X(k*32+ 31),
                WTOS_Y(i*32+31), 0xff8800);
            }
        }
    }
}

void cmLevel::clear_data() {
}
