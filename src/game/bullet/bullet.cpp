#include "bullet.h"

using namespace std;

class cBullet *cmBullet::add(const char *id, cVector pos, cVector vel) {

    class cBullet *newBullet;
    newBullet = new cBullet(get(id), pos, vel);
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

        if (tmp->life % 8 == 0) {
            tmp->animation->setSequence("FRAMEA");
        } else {
            tmp->animation->setSequence("FRAMEB");
        }

        ++tmp->life;
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
       cBullData *tmp = new cBullData;
       tmp->script = mGame->mFile->get_script((*i).c_str());
       LOGS(LDEBUG, "Loading bullet %s",
             mGame->mFile->execdir_strip((*i).c_str()).c_str());
             insert(mGame->mFile->execdir_strip((*i).c_str()), tmp);
    }
    return 0;
}
