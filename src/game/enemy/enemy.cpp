#include "enemy.h"

/*
 * Initialize enemy.
 */
void cmEnemy::init() {
    add(NULL);
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

class cEnemy *cmEnemy::add(char *script) {

    cEnemy *e = new cEnemy(new cEnemyData);

    e->height = 128;    /* should be height of sprite */
    e->width = 128;     /* should be width of sprite */
    e->animation = mGame->mAnim->add("EULER");
    e->animation->setSequence("EVIL");

    /* testing purposes */
    e->pos = cVector(300, SCREEN_H - e->height - 24);

    enemies.push_back(e);

    return e;
}

void cmEnemy::draw(void) {

    std::list<cEnemy*>::iterator it;

    for (it = enemies.begin(); it != enemies.end(); it++) {

        cEnemy *e = *it;
        rectfill(mGame->mDraw->buffer, WTOS_X(int(e->pos.x)),
                WTOS_Y(int(e->pos.y)), WTOS_X(int(e->pos.x)) + e->width,
                WTOS_Y(int(e->pos.y)) + e->height, 0x00ff00);

        e->animation->draw(mGame->mDraw->buffer, WTOS_X(int(e->pos.x)),
                WTOS_Y(int(e->pos.y)));
        // Here goes animation
    }
}
