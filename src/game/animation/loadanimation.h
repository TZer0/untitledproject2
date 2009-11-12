/**
 * File: loadanimation.h
 *
 * Description:	Header file for animation loading.
 *              Stores all loaded animation data
 */
#ifndef ANIMATIONLOAD_H
#define ANIMATIONLOAD_H
// Global includes
#include <vector>
#include <list>
#include "../lua.h"

// Other includes
#include "../port.h"
#include "loadtemplate.h"

/// Data for a single frame of animation
class cAnimFrameData {
	public:
		BITMAP *bmp;
		
		int xo,yo; // Offset for this bitmap
		
		/// Time to display this frame (in sec.)
		double t;
};

/// Data for an animation sequence
class cAnimSeqData {
	public:
		/// Frame data
		std::vector<class cAnimFrameData *>fd;
		
		double maxt; // Cumulative length of sequence in seconds
		std::string next;
		
		int id; // Numerical ID for this sequence
		
		/// For creating a new frame in sequence
		cAnimFrameData *new_frame(BITMAP *bmp, int xof, int yof, double tm) {
		    cAnimFrameData *tmp = new cAnimFrameData;
		    
		    // Setting frame data
		    tmp->bmp = bmp;
		    tmp->xo = xof;
		    tmp->yo = yof;
		    tmp->t = tm;
		    maxt+=tm;
		    
		    fd.push_back(tmp);
		    return tmp;
		}
};

/// Data for an animation 
class cAnimData {
	public:
		/// Sequence data
		std::map<std::string,cAnimSeqData *>
			sqd;
		
		/// Sequence vector.
		/// Generated after loading all id strings
		std::vector<cAnimSeqData *>sqv;
		
		/// For creating a new sequence in animation
		cAnimSeqData *new_sequence(std::string id, std::string next="") {
		    cAnimSeqData *tmp = new cAnimSeqData;   // Allocating memory
		    sqd[id] = tmp;                          // Pushing it into the sequence map
		    
		    tmp->id = sqv.size();                   // Gets the sequence ID
		    sqv.push_back(tmp);                     // Pushing it into the sequence vector
		    
		    tmp->next = next;                       // Defining the "next" frame for the sequence
		    tmp->maxt = 0.0;                        // Zero as it has no frames
		    return tmp;                             // Returning the allocated sequence pointer
		}
};

/**
 * Animation data module
 */
class cmAnimData : public tLoadingSystem<cAnimData *> {
    public:
        cAnimData *cur;
        cAnimSeqData *cseq;
        cAnimFrameData *cframe;
        BITMAP *seqBmp;
};


// Function definitions
int anim_getItems(void);
int anim_load(void);

#endif

