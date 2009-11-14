#include "../port.h"
#include "level.h"
#include "../draw.h"
#include "../game.h"
#include <algorithm>

using namespace std;

void cmLevel::init() {

    // todo: put this call where it really belongs:
    load();

    tiles.resize(LEVEL_HEIGHT);
    for (int j = 0; j<LEVEL_HEIGHT; j++) {
        tiles[j].resize(LEVEL_WIDTH);
                tiles[j][21] = 1;
    }
    tiles[10][20] = 1;
    tiles[10][19] = 1;
    tiles[10][18] = 1;
    
    rect = mGame->mCollision->create(CollisionRectangle, &colpos, cVector(0,0), 32, 32);
    
    // Register the tiles to the collision map
    for (int k = 0; k<LEVEL_WIDTH; k++) {
        for (int i = 0; i<LEVEL_HEIGHT; i++) {
            if(tiles[k][i] != 0) {
                // Moves the collision position
                colpos = cVector(k*32, i*32);
            
                // Registers the rectangle for all existing tiles
                register_collision(rect, new sColSectorInstance(new sLevelCollision(k,i)));
            }// if(isTile)
        }// for(y)
    }// for(x)
    
}

void cmLevel::collision_function(int caller_id, void *inst)
{
    // Retrieving our sLevelCollision which is hidden in that void *
    sLevelCollision *lc = (sLevelCollision*)inst;
    
    // Move the collision position vector (which is attached to our collision object)
    colpos = cVector(lc->xi*32, lc->yi*32);
    
    // Call the test_collision() function for the cApplyCollision system that called for us
    // Passing our collision object, and our number
    getCaller()->test_collision(getId(), rect);
}

void cmLevel::level_init() {
}

int cmLevel::load() {
    PACKFILE *pf;
    string filename;

    // creates a new levelinfo instance.
    // todo: create more instances and put them in the levelinfo map.
    curLev = new cLevelInfo();

    LOGL(LDEBUG, "Loading levelinfo..");

    // opens the levelfile (todo: make a way to choose a file)
    filename = mGame->mFile->get_filename("levels","levelinfo.lvl");
    pf = pack_fopen(filename.c_str(), "r");
    if (!pf){
        LOGL(LERR, "pack_fopen(%s) failed", filename.c_str());
        return 1; // hope this is what we are supposed to return..
    }

    curLev->load(pf);
    pack_fclose(pf);

    // resize level size:
    tiles.resize(curLev->get_sizex());

    for (int x=0; x < get_sizex(); x++){
        tiles[x].resize(get_sizey());
    }

    LOGL(LDEBUG, "Loading tiles..");

    // open tile file:
    filename = mGame->mFile->get_filename("levels", curLev->get_mapfile().c_str());
    pf = pack_fopen(filename.c_str(), "r");
    if (!pf){
        LOGL(LERR, "pack_fopen(%s) failed", filename.c_str());
        return 1;
    }

    for (int y=0; y < get_sizey(); y++){
        for (int x=0; x < get_sizex(); x++){
            tiles[x][y] = pack_igetl(pf);
        }
    }

    pack_fclose(pf);

    return 0;
}

void cmLevel::process(double delta) {
}

void cmLevel::draw() {
    int i, k;
    for (k = 0; k<LEVEL_WIDTH; k++){
        for (i = 0; i<LEVEL_HEIGHT; i++){
            if (tiles[k][i] == 1){
            rectfill(mGame->mDraw->buffer, WTOS_X(k*32), WTOS_Y(i*32),WTOS_X(k*32+ 31),
                WTOS_Y(i*32+31), 0xff8800);
            }
        }
    }
}

void cmLevel::clear_data() {
}