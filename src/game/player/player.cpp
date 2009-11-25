#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"
#include "../level/level.h"

#define OUTER_BORDER_W 200
#define INNER_BORDER_W 300
#define OUTER_BORDER_H 150
#define INNER_BORDER_H 200

/*
 * Initialize player.
 */
void cmPlayer::init() {
    gravity = 1600.0;
    horSpeed = 250;
    jumpHeight = 400;
    jumpLife = JUMP_LIFE;
    height = 48;
    width = 32;

    pos = cVector(200, SCREEN_H - height - 50);
    vel = cVector(0.0, 0.0);

    // Initate camera position
    mGame->mDraw->set_cam(pos.x-SCREEN_W/2, pos.y-SCREEN_H/2);

    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
    flagFire = false;
    left = false;
    reJump = false;

    animation = mGame->mAnim->add("PLAYER");
    animation->setSequence("IDLE");

    col = mGame->mCollision->create(CollisionRectangle, &pos, cVector(0,0),
            32, 48);

    // Give the player a weapon.
    LOGS(LDEBUG, "Adding player weapon...");
    weapon = mGame->mWeapon->add("data/weapons/bfg9k1.lua", -1, false);
    LOGS(LDEBUG, "Weapon pointer: %p.", weapon);
    LOGS(LDEBUG, "Added player weapon...");
}

/*
 * Set player flags based on keyboard input.
 */
void cmPlayer::input() {
    reJump = true;
    if (key[KEY_LEFT] || key[KEY_H]) {
        flagLeft = true;
    }

    if (key[KEY_RIGHT] || key[KEY_L]) {
        flagRight = true;
    }

    if (key[KEY_UP] || key[KEY_K]) {
        flagUp = true;
        reJump = false;
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
    prevy = pos.y;
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
    
    // old code:
    /*
    mGame->mDraw->set_cam(pos.x-SCREEN_W/2, pos.y-SCREEN_H/2);
    */

    /*
        Makes the camera follow only when the player is approaching the border,
        that meaning that there is a zone in the middle of the screen where the
        camera does not follow at all, an inner border where the camera follows
        with delay, and an outer border where the camera follows the player at
        the same speed as the player.

        OUTER_BORDER_W/_H and INNER_BORDER_W/_H is currently defined at the top 
        of this document.
    */

    cVector cam = mGame->mDraw->get_cam();
    cVector player = mGame->mDraw->wtos(pos);
    if (player.x < OUTER_BORDER_W)            cam.x = pos.x - OUTER_BORDER_W;
    if (player.x > SCREEN_W - OUTER_BORDER_W) cam.x = pos.x + OUTER_BORDER_W - SCREEN_W;
    if (player.y < OUTER_BORDER_H)            cam.y = pos.y - OUTER_BORDER_H;
    if (player.y > SCREEN_H - OUTER_BORDER_H) cam.y = pos.y + OUTER_BORDER_H - SCREEN_H;
    
    // Here different formulas can be applied to give desired effect, f.ex can
    // the camera move slower if the player is closing to the center of the
    // screen, or the camera wont move in this region if the player is moving
    if (player.x < INNER_BORDER_W)            cam.x -= delta * horSpeed/3;
    if (player.x > SCREEN_W - INNER_BORDER_W) cam.x += delta * horSpeed/3;
    if (player.y < INNER_BORDER_H)            cam.y -= delta * horSpeed/3;
    if (player.y > SCREEN_H - INNER_BORDER_H) cam.y += delta * horSpeed/3;

    // Please notice that if the player is inside the inner border, then nothing
    // happens to cam, so it was necessary to know where the camera initially was.
    mGame->mDraw->set_cam(cam.x, cam.y);
    mGame->mDraw->cam_cap();
}

/*
 * Draw player sprite.
 */
void cmPlayer::draw() {
    /*
    rectfill(mGame->mDraw->buffer, WTOS_X(int(pos.x)), WTOS_Y(int(pos.y)),
            WTOS_X(int(pos.x)) + width, WTOS_Y(int(pos.y)) + height,
            0xff8800);
            */
    // UGLY!

    // Testing animation
    animation->draw(mGame->mDraw->buffer, WTOS_X(int(pos.x)),
            WTOS_Y(int(pos.y)));
}

/*
 * Reset player position and velocity.
 */
void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}

/**
 * Called by the one when collide with
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
        if (fabs(angle-M_PI/2.0) < 0.01 && vel.y > 0) {
            // Currently, we kill off the velocity, based on the the
            // return path normal
            vel = vel*ret.orp.normal().norm();
            if (reJump == true) {
                jumpLife = JUMP_LIFE;
            }
        }
        
        if (fabs(angle+M_PI/2.0) < 0.01) {
            if (prevy == pos.y) {
                // Currently, we kill off the velocity, based on the the
                // return path normal
                vel = vel*ret.orp.normal().norm();
                jumpLife = 0;
            }
        }
        

        return true;
    }
    return false;
}
