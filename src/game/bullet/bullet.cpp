#include "bullet.h"

using namespace std;

class cBullet *cmBullet::add(const char *script, cVector pos, cVector vel) {

    class cBullet *newBullet;
    newBullet = new cBullet(script, pos, vel);
    bullets.push_back(newBullet);
    return newBullet;
}

void cmBullet::draw(void) {
    for (EatBullets i = bullets.begin(); i!=bullets.end(); i++) {
        cBullet *tmp = (*i);
        tmp->animation->draw(mGame->mDraw->buffer, int(WTOS_X(tmp->pos.x)),
                int(WTOS_Y(tmp->pos.y))); 
    }

}

void cmBullet::process(double delta) {
    for (EatBullets i = bullets.begin(); i!=bullets.end(); i++) {
        cBullet *tmp = (*i);
        tmp->pos += tmp->vel * delta;
    }
}

void cmBullet::clear_data(void) {
    for (EatBullets i = bullets.begin(); i != bullets.end(); i++)
        delete (*i);
}

int cmBullet::load(void) {
    // Fetches all the files in the directory named "bullet" with the suffix
    // .lua(*.lua)
    
    cmBullData *cmBD = mGame->mBullet->bullData;
    cmBD->filedb = mGame->mFile->dirRecursiveGet("bullet", "lua");
    
    std::list<std::string>::iterator i;
    
    for (i = cmBD->filedb.begin(); i != cmBD->filedb.end(); i++) {
       // LOGS(DEBUG, "Loading %s", (*i).c_str());
       // load_bullet_file((*i).c_str());
    }
    return 0;
}
