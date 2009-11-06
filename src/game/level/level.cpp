#include "../port.h"
#include "level.h"
#include "../draw.h"
#include "../game.h"
void cmLevel::init() {
    tiles[0][0] = 0;
    tiles[0][1] = 0;
}

void cmLevel::level_init() {
}

int cmLevel::load() {
    return 0;
}

void cmLevel::process(double delta) {
}

void cmLevel::draw() {
       rectfill(mGame->mDraw->buffer, tiles[0][0], tiles[0][0], 32,
           32, 0xff8800);
}

void cmLevel::clear_data() {
}
