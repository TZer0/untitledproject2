#include "../port.h"
#include "level.h"
#include "../draw.h"
#include "../game.h"
void cmLevel::init() {
    tiles[0][0] = 1;
    tiles[0][1] = 1;
    tiles[1][0] = 1;
    tiles[1][1] = 1;
    tiles[2][0] = 1;
    tiles[2][1] = 1;
    tiles[3][0] = 1;
    tiles[3][1] = 1;
    tiles[4][0] = 1;
    tiles[4][1] = 1;
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
    for (k = 0; k<5; k++){
        for (i = 0; i<5; i++){
            if (tiles[k][i] == 1){
            rectfill(mGame->mDraw->buffer, k*32, i*32,k*32+ 32,
                i*32+32, 0xff8800);
            }
        }
    }
}

void cmLevel::clear_data() {
}
