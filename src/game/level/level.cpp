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

void cmLevel::draw() {
       rectfill(mGame->mDraw->buffer, 0, 0, 32,
           32, 0xff8800);
}

void cmLevel::clear_data() {
}
