/**
 * File: loadanimation.cpp
 *
 * Description:	Handles loading of animations
 *
 * (c)2009, by Raymond Loeberg
 */
// Global includes
#include "../../port.h"
#include "../../game.h"

// Loading includes
#include "loadanimation.h"
#include "../loadimage.h"

// Module includes
#include "anim.h"

// Other includes
#include "../file.h"
#include "../log.h"

// Lua includes
#include "luaanimation.h"

int anim_getItems(void)
{
	mGame->mAnim->animData->filedb = mGame->mFile->dirRecursiveGet("animations", "lua");
	return(mGame->mAnim->animData->filedb.size());
}

/**
 * Loads an animation file by running a lua script
 */
void load_anim_file(const char *file)
{
    lua_State *l;
    
    l = luaL_newstate();
    luaL_openlibs(l);
    luaanim_open(l);
    
    if(luaL_dofile(l, file)) {
        goto cleanup;
    }
    
    lua_close(l);
    
    cleanup:
    
    return;
}

/**
 * Iterates through the indexes of files to load
 * and calls functions to load them
 */
int anim_load(void)
{
	std::list<std::string>::iterator i;
	
	// Load animations as LUA scripts
	for(i=mGame->mAnim->animData->filedb.begin(); i!=mGame->mAnim->animData->filedb.end(); i++) {
	    LOGS(LDEBUG, "Loading %s", (*i).c_str());
	    load_anim_file((*i).c_str());
	    
	    mGame->mAnim->animData->cur = NULL;
	    mGame->mAnim->animData->cseq = NULL;
	}
	
	return 0;
}
