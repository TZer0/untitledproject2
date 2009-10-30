#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"

void cmPlayer::init() {

}

void cmPlayer::input() {

}

void cmPlayer::process(double delta) {

}

void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, 50, 50, 100, 100, 100);
}

void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
