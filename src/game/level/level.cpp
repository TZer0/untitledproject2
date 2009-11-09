#include "../port.h"
#include "level.h"
#include "../draw.h"
#include "../game.h"
void cmLevel::init() {
    tiles[0][0] = 0;
    tiles[0][1] = 0;
    tiles[1][0] = 1;
    tiles[1][1] = 1;
    tiles[2][0] = 2;
    tiles[2][1] = 2;
    tiles[3][0] = 3;
    tiles[3][1] = 3;
    tiles[4][0] = 4;
    tiles[4][1] = 4;
}

void cmLevel::level_init() {
}

int cmLevel::load() {
    return 0;
}

void cmLevel::process(double delta) {
}

void cmLevel::draw() {
    int i;
    for (i = 0; i<5; i++){
       rectfill(mGame->mDraw->buffer, tiles[i][0]*32, tiles[i][1]*32,tiles[i][0]*32+ 32,
           tiles[i][1]*32+32, 0xff8800);
    }
}

void cmLevel::clear_data() {
}
