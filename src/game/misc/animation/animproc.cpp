/**
 * File: animproc.cpp
 *
 * Description:	Processes animations
 */
// Global headers
#include <math.h>

// Module headers
#include "anim.h"

/**
 * Processes all animations in the module
 */
void cmAnim::process(double delta)
{
	double dr; // Reduced delta
	
	// Helper variables
	class cAnimation *cur;
	class cAnimSeqData *cseq;
	
	for(AnimIter i=data.begin(); i!=data.end(); i++) {
		// "Define" the current object and sequence
		cur=(*i);
		cseq = cur->cseq;
		
		// Check if this object is to be killed
		if(cur->toDie) {
		    data.erase(i);
			continue;
		}
		
		// We prevent the delta from being too fucking large
		// o_O
		// Also: Multiply by the current animation speed
		dr = fmod(delta*cur->speed ,cseq->maxt);
		
		// Increment the delta
		cur->curt+=dr;
		
		// Go to next frame if past the next frame limit
		while(cur->curt >= cur->nt) {
			// These next cryptic lines does what?
			// 		They update the position of the next frame
			cur->nt += cseq->fd[cur->cf]->t;
			cur->cf++;
			
			// Prevent out of bounds
			// Go in circles \o/
			if(cur->cf >= cseq->fd.size()) {		// Check if the current frame passed the number of frames
				// Swap sequence if this sequence requests it
			    if(!cseq->next.empty()) {
			        cur->setSequence(cseq->next,0);
			        continue;
			    }
			    
				cur->cf = 0;						// Revert to first frame..
				cur->nt = cseq->fd[cur->cf]->t;		// ..and set the next animation time to that of the first frame
				
				// Revert curt, cuts off any excess progress
				cur->curt = fmod(cur->curt,cseq->maxt);
			}
		}
		
		// Set the currently displayed image
		cur->cur = cseq->fd[cur->cf]->bmp;
		cur->x = cseq->fd[cur->cf]->xo;
		cur->y = cseq->fd[cur->cf]->yo;
	}
	
	return;
}
