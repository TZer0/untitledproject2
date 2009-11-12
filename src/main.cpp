/**
 * File: main.cpp
 *
 * Description: Main file
 */
#include "game/port.h"
#include "game/game.h"

cmGame *mGame;

int main(int argc, char **argv)
{
    mGame = new cmGame;
    mGame->run();
    
    return 0;
}
END_OF_MAIN()