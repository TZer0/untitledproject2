#include "enemy.h"

/*
 * Initialize enemy.
 */
void cmEnemy::init() {
    add(NULL, cVector(400, 300));
    add(NULL, cVector(350, 20));
    add(NULL, cVector(1000, 500));
}

void cmEnemy::clear_data(void) {
    // clear
}

/* Load the enemy data */
int cmEnemy::load(void) {

    std::list<std::string> files
        = mGame->mFile->dirRecursiveGet("enemies", "lua");

    for (Fileeater f = files.begin(); f != files.end(); f++) {
        std::string tmp = (*f);
        cEnemyData *tmpData = new cEnemyData();
        tmpData->script = mGame->mFile->get_script(tmp.c_str());
    }

    return 0;
}

class cEnemy *cmEnemy::add(char *script, cVector pos) {

    cEnemy *e = new cEnemy(new cEnemyData);

    e->height = 61;    /* should be height of sprite */
    e->width = 57;     /* should be width of sprite */
    e->animation = mGame->mAnim->add("EULER");
    e->animation->setSequence("EVIL");

    /* testing purposes */
    e->pos = pos;

    enemies.push_back(e);

    return e;
}

void cmEnemy::draw(void) {

    std::list<cEnemy*>::iterator it;

    for (it = enemies.begin(); it != enemies.end(); it++) {

        cEnemy *e = *it;
        /*
        rectfill(mGame->mDraw->buffer, WTOS_X(int(e->pos.x)),
                WTOS_Y(int(e->pos.y)), WTOS_X(int(e->pos.x)) + e->width,
                WTOS_Y(int(e->pos.y)) + e->height, 0xffff00);
        */
        // Ugly!

        e->animation->draw(mGame->mDraw->buffer, WTOS_X(int(e->pos.x)),
                WTOS_Y(int(e->pos.y)));

        // Here goes animation
    }
}

void cmEnemy::process(double delta) {
    std::list<cEnemy*>::iterator it;

    for (it = enemies.begin(); it != enemies.end(); it++) {
        cEnemy *e = *it;
        e->vel.x = 0.04 * (mGame->mPlayer->pos.x - e->pos.x);
        e->vel.y = 0.04 * (mGame->mPlayer->pos.y - e->pos.y);
        e->pos += e->vel;

        if (e->life % 60 == 0) {
            LOGS(LDEBUG, "Die, player!");
            e->weapon->fire(e->pos, cVector(10*e->vel.x, 10*e->vel.y));
        }

        ++e->life;
    }
}
