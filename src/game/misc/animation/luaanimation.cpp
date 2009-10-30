#include "luaanimation.h"
#include "loadanimation.h"
#include "../loadimage.h"

// Hidden functions
/**
 * Creates a new animation with the designated ID
 */
static int luaanim_new_animation(lua_State *l)
{
	mAnimData.cur = new cAnimData;
	mAnimData.insert(luaL_checkstring(l,1),mAnimData.cur);
	
	return 0;
}

/**
 * Creates a raw new sequence and adds it to the current animation
 */
static int luaanim_new_sequence(lua_State *l)
{
	// Create sequence in animation
	mAnimData.cseq = mAnimData.cur->new_sequence(luaL_checkstring(l,1), luaL_checkstring(l,3));
    
    // Find bitmap to use for all frames
    mAnimData.seqBmp = mImagesData.retrieve(luaL_checkstring(l,2));
    
	return 0;
}



static int luaanim_new_frame(lua_State *l)
{
    // Stuff it with data
    double t = luaL_checknumber(l, 1);
    
    // Read bitmap location
    int x,y,w,h;
    x = luaL_checkint(l,2);
    y = luaL_checkint(l,3);
    w = luaL_checkint(l,4);
    h = luaL_checkint(l,5);
    BITMAP *bmp = create_sub_bitmap(mAnimData.seqBmp, x,y,w,h);
    
    // Read bitmap offset
    int xo = luaL_checkint(l,6);
    int yo = luaL_checkint(l,7);
    
    // Push frame
    mAnimData.cseq->new_frame(bmp, xo,yo,t);
    
    return 0;
}
// End of hidden functions

static const struct luaL_reg lua_animation[] =
{   {"new_animation", luaanim_new_animation},
    {"sequence", luaanim_new_sequence},
    {"frame", luaanim_new_frame},
    {NULL, NULL}
};

void luaanim_open(lua_State *l)
{
	luaL_register(l, "_G", lua_animation);
	lua_pop(l,1);
}
