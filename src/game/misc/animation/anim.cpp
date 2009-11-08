/**
 * File: anim.cpp
 *
 * Description:	Handles creation and manipulation of animations.
 */
#include "anim.h"

#include "../../game.h"

using namespace std;

// cmAnim functions:
class cAnimation *cmAnim::add(string id)
{
	// Only a wrapper for a different loader
	return add(mGame->mAnim->animData->get(id.c_str()));
}

/**
 * Allocates memory for a new animation and stores it in the database.
 */
class cAnimation *cmAnim::add(cAnimData *animdata)
{
	class cAnimation *tmp;
	
	// Create animation
    tmp = new cAnimation;
	
	// Point to loaded data
	tmp->anim = animdata;
	
	// Set the current sequence and other data
	tmp->cur = NULL; 
	tmp->cseq = NULL;
	tmp->cf = 0;
	tmp->nt = 0.0;
	
	// Set the alive state
	tmp->toDie = 0;
	
	// Append data
	data.push_back(tmp);
	
	return tmp;
}

int cmAnim::load(void)
{
    anim_getItems();
    anim_load();

    return 0;
}

/**
 * Remove all animations
 */
void cmAnim::clear_data(void)
{
    for(AnimIter i = data.begin(); i!=data.end(); i++) {
        delete (*i);
    }    
    
    data.clear();
}

// cAnimation functions:
/**
 * Switches the current animation to a new one
 * @param id The id string to switch to
 */
void cAnimation::setSequence(string id, double curpos)
{
	std::vector<class cAnimFrameData *>::iterator i;
	cseq = anim->sqd[id.c_str()];
	curt = curpos;
	
	// Iterate to find the next frame
	cf=0;
	for(i=cseq->fd.begin();i!=cseq->fd.end();i++) {
		nt+=(*i)->t;
		if(nt>curpos) break;
		cf++;
	}
	
	cur = cseq->fd[cf]->bmp;
	x = cseq->fd[cf]->xo;
	y = cseq->fd[cf]->yo;
}

/**
 * Switches the current animation to a new one
 * @param id The id number to switch to
 */
void cAnimation::setSequence(int id,double curpos)
{
	std::vector<class cAnimFrameData *>::iterator i;
	cseq = anim->sqv[id];
	curt = curpos; // Resets the frame timer
	
	// NOTE: Maybe not duplicate code like this?
	// Iterate to find the next frame
	cf=0;
	for(i=cseq->fd.begin();i!=cseq->fd.end();i++) {
		nt+=(*i)->t;
		if(nt>curpos) break;
		cf++;
	}

	cur = cseq->fd[cf]->bmp;
	x = cseq->fd[cf]->xo;
	y = cseq->fd[cf]->yo;
}

/**
 * Retireves the ID number for a sequence
 * to speed up retrieval
 * @param id The sequence id to retrieve
 */
int cAnimation::getSequence(string id)
{
	return(anim->sqd[id.c_str()]->id);
}

/**
 * Draw an animation to a bitmap
 *
 * @param dest Bitmap to draw to
 * @param xpos X position to draw at
 * @param ypos Y position to draw at
 */
void cAnimation::draw(BITMAP *dest, int xpos,int ypos)
{
    draw_sprite(dest, cur, xpos-x, ypos-y);
}

/**
 * Draws a tinted animation
 */
void cAnimation::draw_lit(BITMAP *dest, int xpos,int ypos, int tint)
{
    draw_lit_sprite(dest, cur, xpos-x, ypos-y, tint);
}
