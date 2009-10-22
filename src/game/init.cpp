#include "game.h"
#include "draw.h"
int cmGame::init(void)
{
    mDraw = new cmDraw;

    mDraw->init();
    return 0;
}
