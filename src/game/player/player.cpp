#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"

void cmPlayer::init() {
    pos = cVector(200, 50);
    vel = cVector(0, 0);
    acc = cVector(0, 0);
    gravity = 1.1;
    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
    inAir = true;
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
    } else {
        vel = cVector(0, vel.y);
    }

    if (!inAir && flagUp) {
        inAir = true;
        acc = cVector(acc.x, -1 * JUMP_HEIGHT);
        vel = cVector(vel.x, acc.y);
    }

    /* Temp. coll. detection, before we get some real ground */
    if (pos.y >= SCREEN_H - 100) {
        vel = cVector(vel.x, 0);
        pos.y = SCREEN_H - 100;
        inAir = false;
    } else {
        acc = cVector(acc.x, acc.y + gravity);
    }
    
    vel = cVector(vel.x + acc.x * delta, vel.y + acc.y * delta);

    pos += vel;
    flagUp = false;
}

void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, pos.x, pos.y, pos.x + 100,
            pos.y + 100, 200);
}

void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
