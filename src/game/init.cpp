#include "misc/timer.h"
#include "game.h"
#include "draw.h"
int cmGame::init(void)
{
    mDraw = new cmDraw;
    mTimer = new cmTimer;

    mDraw->init();
    mTimer->init();
    return 0;
}
