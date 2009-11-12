#include "enemy.h"

/*
 * Initialize enemy.
 */
void cmEnemy::init() {

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

    return NULL;
}
