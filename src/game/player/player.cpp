#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"
#include <stdio.h>

void cmPlayer::init() {
    pos = cVector(200, 50);
    gravity = 105;
    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
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
        vel = cVector(delta * -HOR_SPEED, vel.y);
    } else if (flagRight) {
        flagRight = false;
        vel = cVector(delta * HOR_SPEED, vel.y);
    } else if (flagUp) {
        flagUp = false;
        vel = cVector(vel.x, 1);
    } else {
        vel = cVector(0, vel.y);
    }

    /* Temp. coll. detection, before we get some real ground */
    if (pos.y >= SCREEN_H - 100) {
        vel = cVector(vel.x, 0);
        pos.y = SCREEN_H - 100;
    } else {
        vel = cVector(vel.x, delta * (vel.y * gravity));
    }

    printf("%f\n", vel.y);
    pos += vel;
}

void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, pos.x, pos.y, pos.x + HOR_SPEED,
            pos.y + HOR_SPEED, 200);
}

void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
