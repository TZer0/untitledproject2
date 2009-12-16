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
	filedb = mGame->mFile->dirRecursiveGet("enemies", "lua");
	FileIterator f;
    for (f = filedb.begin(); f != filedb.end(); f++) {
        std::string tmp = (*f);
        cEnemyData *tmpData = new cEnemyData();
        tmpData->script = mGame->mFile->get_script(tmp.c_str());
    }
    return 0;
}

class cEnemy *cmEnemy::add(char *script, cVector pos) {

    cEnemy *e = new cEnemy(new cEnemyData);

    e->height = 16;    /* should be height of sprite */
    e->width = 9;     /* should be width of sprite */
    e->animation = mGame->mAnim->add("BUMBLE");
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
    cVector vel;

    for (it = enemies.begin(); it != enemies.end(); it++) {
        cEnemy *e = *it;
        e->vel.x = 0.04 * (mGame->mPlayer->pos.x - e->pos.x+15);
        e->vel.y = 0.04 * (mGame->mPlayer->pos.y - e->pos.y+25);
        e->pos += e->vel;
        // LOGS(LDEBUG, "e->life: %f", e->life);
        if (int(e->life) % 100 == 0) {
            LOGS(LDEBUG, "Die, player!");
            vel = cVector(10*e->vel.x, 10*e->vel.y);
            e->weapon->fire(e->pos, vel.snorm());
        }

        e->life += 100 * delta;
    }
}
