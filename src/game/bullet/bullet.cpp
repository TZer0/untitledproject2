#include "bullet.h"

using namespace std;

class cBullet *cmBullet::add(char *script, cVector pos, cVector vel) {
    
    class cBullet *newBullet;
    newBullet = new cBullet(script, pos, vel);
    bullets.push_back(newBullet);
    return newBullet;
}

class cBullet *cmBullet::draw() {
   animation->draw(mGame->mDraw->buffer, int(pos.x), int(pos.y)); 
}

class cBullet *cmBullet::process(double delta) {
    pos += vel * delta;
}

