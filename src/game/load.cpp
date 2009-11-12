#include "misc/log.h"
#include "animation/anim.h"

#include "game.h"

void cmGame::load(void)
{
    LOGL(LNOTE, "Loading data");

    mAnim->load();
}
