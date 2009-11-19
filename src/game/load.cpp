#include "misc/log.h"
#include "animation/anim.h"
#include "level/level.h"
#include "game.h"

void cmGame::load(void)
{
    LOGL(LNOTE, "Loading data");
    mLevel->load();
    mAnim->load();
}