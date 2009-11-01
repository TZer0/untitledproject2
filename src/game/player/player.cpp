#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"

/*
 * Initialize player.
 */
void cmPlayer::init() {
    pos = cVector(200, 50);
    vel = cVector(0, 0);
    acc = cVector(0, 0);
    gravity = 1.1;
    horSpeed = 48;
    jumpHeight = 8;
    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
    inAir = true;
}

/*
 * Set player flags based on keyboard input.
 */
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

/*
 * Process player flags. Update player position.
 *
 * @param delta Delta
 */
void cmPlayer::process(double delta) {
    // Update horizontal velocity and clear flags.
    if (flagLeft) {
        flagLeft = false;
        vel = cVector(delta * -horSpeed, vel.y);
    } else if (flagRight) {
        flagRight = false;
        vel = cVector(delta * horSpeed, vel.y);
    } else {
        vel = cVector(0, vel.y);
    }

    // Jump handling.
    if (!inAir && flagUp) {
        inAir = true;
        acc = cVector(acc.x, -1 * jumpHeight);
        vel = cVector(vel.x, acc.y);
    }

    // Temporary collision detection. Uses screen height instead of ground.
    if (pos.y >= SCREEN_H - 100) {
        vel = cVector(vel.x, 0);
        pos.y = SCREEN_H - 100;
        inAir = false;
    } else {
        acc = cVector(acc.x, acc.y + gravity);
    }
    
    // Update vertical velocity and clear flags.
    vel = cVector(vel.x + acc.x * delta, vel.y + acc.y * delta);
    pos += vel;
    flagUp = false;
}

/*
 * Draw player sprite.
 */
void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, pos.x, pos.y, pos.x + 100,
            pos.y + 100, 0xff8800);
}

/*
 * Reset player position and velocity.
 */
void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
