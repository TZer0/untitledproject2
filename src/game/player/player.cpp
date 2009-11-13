#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"
#include "../level/level.h"

/*
 * Initialize player.
 */
void cmPlayer::init() {
    // gravity = 1000.0;
    gravity = 0.0;
    horSpeed = 300;
    jumpHeight = 400;
    jumpLife = JUMP_LIFE;
    height = 48;
    width = 32;
    
    pos = cVector(200, SCREEN_H - height);
    vel = cVector(0.0, 0.0);

    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
    flagFire = false;
    left = false;
    
    animation = mGame->mAnim->add("PLAYER");
    animation->setSequence("IDLE");
    
    col = mGame->mCollision->create(CollisionRectangle, &pos, cVector(0,0), 32, 48);

    // Give the player a weapon.
    LOGS(LDEBUG, "Adding %s...", "player weapon");
    weapon = mGame->mWeapon->add("print(1)\n", -1, false);
    LOGS(LDEBUG, "Weapon pointer: %p.", weapon);
    LOGS(LDEBUG, "Added %s...", "player weapon");
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

    if (key[KEY_X]) {
        flagFire = true;
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
        animation->setSequence("LEFT");
        left = true;
    } else if (flagRight) {
        flagRight = false;
        vel.x = horSpeed;
        animation->setSequence("RIGHT");
        left = false;
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
    
    // Test for collision
    mGame->mLevel->apply_collision(this, col);

    // Temporary collision detection.
    // Uses screen height instead of ground.
    /*if (pos.y >= SCREEN_H - height) {
        vel.y = 0;
        pos.y = SCREEN_H - height;
        jumpLife = JUMP_LIFE;
    }*/

    if (flagFire) {
        cVector bulVel;
        flagFire = false;
        if (left) {
            bulVel.x = -3 * horSpeed;
        } else {
            bulVel.x = 3 * horSpeed;
        }
        weapon->fire(pos, bulVel);
    }
    mGame->mDraw->set_cam(pos.x-SCREEN_W/2, pos.y-SCREEN_H/2);
}

/*
 * Draw player sprite.
 */
void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, WTOS_X(int(pos.x)), WTOS_Y(int(pos.y)), WTOS_X(int(pos.x)) + width,
            WTOS_Y(int(pos.y)) + height, 0xff8800);
    
    // Testing animation
    animation->draw(mGame->mDraw->buffer, WTOS_X(int(pos.x)), WTOS_Y(int(pos.y)));
}

/*
 * Reset player position and velocity.
 */
void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}

/**
 * Called by the one whe collide with
 */
bool cmPlayer::test_collision(int dial_id, cCollision *target)
{
    sColReturn ret = col->collide(target, vel);
    
    if(ret.isCol) {
        switch(dial_id)
        {
            case MOD_LEVEL:
                pos+=ret.orp;
            break;
        }
        
        // We will also permit a new jump, if the normal is sensible.
        double angle = ret.orp.angle();
        if(fabs(angle-M_PI/2.0) < 0.1) {
            // Currently, we kill off the velocity, based on the the return path normal
            vel = vel*ret.orp.normal().norm();
            jumpLife = JUMP_LIFE;
        }
        
        return true;
    }
    return false;
}
