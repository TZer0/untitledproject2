#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"

/*
 * Initialize player.
 */
void cmPlayer::init() {
    gravity = 750.0;
    horSpeed = 180;
    jumpHeight = 300;
    jumpLife = JUMP_LIFE;
    height = 64;
    width = 64;
    
    pos = cVector(200, SCREEN_H - width);
    vel = cVector(0.0, 0.0);

    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
}

/*
 * Set player flags based on keyboard input.
 */
void cmPlayer::input() {
    if (key[KEY_LEFT] || key[KEY_H]) {
        flagLeft = true;
    }

    if (key[KEY_RIGHT] || key[KEY_L]) {
        flagRight = true;
    }

    if (key[KEY_UP] || key[KEY_K]) {
        flagUp = true;
    }

    if (key[KEY_DOWN] || key[KEY_J]) {
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
        vel.x = -horSpeed;
    } else if (flagRight) {
        flagRight = false;
        vel.x = horSpeed;
    } else {
        vel.x = 0;
    }

    // Jump handling.
    if (flagUp) {
        if (jumpLife > 0) {
            vel.y = -jumpHeight;
            jumpLife -= delta;
        }
        flagUp = false;
    } else {
        // If button is let, you can not jump again in the same jump
        jumpLife = 0;
    }

    // Update vertical velocity and position
    vel.y += gravity * delta;
    pos += vel * delta;

    // Temporary collision detection.
    // Uses screen height instead of ground.
    if (pos.y >= SCREEN_H - height) {
        vel.y = 0;
        pos.y = SCREEN_H - height;
        jumpLife = JUMP_LIFE;
    }
}

/*
 * Draw player sprite.
 */
void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, pos.x, pos.y, pos.x + width,
            pos.y + height, 0xff8800);
}

/*
 * Reset player position and velocity.
 */
void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
