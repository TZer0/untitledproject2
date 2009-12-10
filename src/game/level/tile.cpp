#include "tile.h"   

// The important thing here is to keep these two fuctions inverse
// of each other

#define TO_TILE(attr, bit) \
    attr = iTile & ((1 << bit) - 1); iTile >>= bit 

cTile::cTile(int iTile){
    TO_TILE(tile,         8);
    TO_TILE(ladder,       1);
    TO_TILE(slippery,     5);
    TO_TILE(kill,         2);
    TO_TILE(invisible,    1);
    TO_TILE(destroyable,  1);
    TO_TILE(water,        1);
    TO_TILE(sink,         1);
    TO_TILE(scriptdef,    4);
    TO_TILE(notbigbox,    1);
    TO_TILE(notcollidable,1);
    TO_TILE(unknown,      6);
}

#undef TO_TILE

#define FROM_TILE(attr, bit) iTile <<= bit; iTile |= attr

int cTile::to_int(){
    int iTile = 0;

    FROM_TILE(unknown,      6);
    FROM_TILE(notcollidable,1);
    FROM_TILE(notbigbox,    1);
    FROM_TILE(scriptdef,    4);
    FROM_TILE(sink,         1);
    FROM_TILE(water,        1);
    FROM_TILE(destroyable,  1);
    FROM_TILE(invisible,    1);
    FROM_TILE(kill,         2);
    FROM_TILE(slippery,     5);
    FROM_TILE(ladder,       1);
    FROM_TILE(tile,         8);

    return iTile;
}

#undef FROM_TILE