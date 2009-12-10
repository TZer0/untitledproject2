#include "weapon/weapon.h"
#include "misc/log.h"
#include "animation/anim.h"
#include "level/level.h"
#include "bullet/bullet.h"
#include "game.h"

void cmGame::load(void)
{
    LOGL(LNOTE, "Loading data");
    // F1RST!
    mBullet->load();
    mWeapon->load();
    mLevel->load();
    mAnim->load();
}
