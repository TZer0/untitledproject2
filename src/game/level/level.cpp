#include "../port.h"
#include "level.h"
#include "../draw.h"
#include "../game.h"
void cmLevel::init() {
}

void cmLevel::level_init() {
}

int cmLevel::load() {
    return 0;
}

void cmLevel::process(double delta) {
}

void cmLevel::draw(int x, int y, int tile) {
    int a, b;
       rectfill(mGame->mDraw->buffer, x*32, y*32, x*32 + 32,
            y + 32, 0xff8800);
}

void cmLevel::clear_data() {
}
