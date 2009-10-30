#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"

void cmPlayer::init() {
    pos = cVector(50, 50);
}

void cmPlayer::input() {
    
    if (key[KEY_LEFT]) {
        flagLeft = true;
    }

    if (key[KEY_RIGHT]) {
        flagRight = true;
    }

    if (key[KEY_UP]) {
        flagUp = true;
    }
    
    if (key[KEY_DOWN]) {
        flagDown = true;
    }
}

void cmPlayer::process(double delta) {

    if (flagLeft) {
        flagLeft = false;
        vel = cVector(delta * -100.0, 0);
    } else if (flagRight) {
        flagRight = false;
        vel = cVector(delta * 100.0, 0);
    } else if (flagUp) {
        flagUp = false;
        vel = cVector(0, delta * -100.0);
    } else if (flagDown) {
        flagDown = false;
        vel = cVector(0, delta * 100.0);
    } else {
        vel = cVector(0, 0);
    }

    pos += vel;
}

void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, pos.x, pos.y, pos.x + 100, pos.y + 100,
            200);
}

void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
