#include "bullet.h"

using namespace std;

class cBullet *cmBullet::add(char *script, cVector pos, cVector vel) {

    class cBullet *newBullet;
    newBullet = new cBullet(script, pos, vel);
    bullets.push_back(newBullet);
    return newBullet;
}

void cmBullet::draw(void) {
    for (EatBullets i = bullets.begin(); i!=bullets.end(); i++) {
        cBullet *tmp = (*i);
        tmp->animation->draw(mGame->mDraw->buffer, int(tmp->pos.x), int(tmp->pos.y)); 
    }

}

void cmBullet::process(double delta) {
    // pos += vel * delta;
    for (EatBullets i = bullets.begin(); i!=bullets.end(); i++) {
        cBullet *tmp = (*i);
        tmp->pos += tmp->vel * delta;
    }

}

