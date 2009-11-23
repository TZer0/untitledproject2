#include "../level/level.h"
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
    for (EatBullets i = bullets.begin(); i!=bullets.end(); /* */) {
        cBullet *tmp = (*i);
        cur = tmp;
        
        // Runs the script function
        lua_getglobal(tmp->l, "process");
        lua_pushnumber(tmp->l, delta);
        lua_pcall(tmp->l, 1, 0, 0);
        
        tmp->pos += tmp->vel * delta;
        
        colpoint = cur->pos;
        mGame->mLevel->apply_collision(this, col);

        ++tmp->life;
        
        if(tmp->toDie) {
            i = bullets.erase(i);
        }else
            ++i;
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

bool cmBullet::test_collision(int dial_id, cCollision *target)
{
    sColReturn ret = col->collide(target, cur->vel);

    if(ret.isCol) {
        cur->toDie = true;
        
        return true;
    }
    return false;
}
