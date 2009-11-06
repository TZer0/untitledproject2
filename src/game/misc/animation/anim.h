/**
 * File: anim.h
 *
 * Description:	Header for the animation module
 *				and animation instance
 */
#ifndef ANIM_H
#define ANIM_H

// Global headers
#include <list>
#include <queue>
#include <vector>
#include <string>

// Module headers

// Loading headers
#include "loadanimation.h"

// Other headers
#include "../../port.h"
#include "../moduletemplate.h"


/// Animation data block
class cAnimation {
    private:
        /// @name Bitmap data
		//@{
			BITMAP *cur;	// Current bitmap
			int x,y;		// Relative position of current bitmap
		//@}
    
	public:
		cAnimation() 
		{cur=NULL;cseq=NULL;anim=NULL;toDie=0;speed=1.0;}
		
		/// @name Misc. variables
		//@{
			double curt;		// Current time position
			double speed;       // Time compression of animation
			
			unsigned int cf;	// Current animation frame
			double nt;			// Time to change to next animation
			
			int toDie;			// Flag determining if the animation should destruct next update
		//@}
		
		/// @name Links to loaded data
		//@{
			class cAnimSeqData *cseq;	// Current sequence
			class cAnimData *anim;		// Loaded data link
		//@}
		
		/// @name Sequence functions
		//@{
            void setSequence(std::string,double curpos=0.0);
            void setSequence(int,double curpos=0.0);
            int getSequence(std::string);
        //@}
		
		/// @name Misc. functions
		//@{
             /// Sets the speed of the animation
            void setSpeed(double speed) { this->speed = speed; }
            
            int getW() { return cur->w; } ///< Retrieve the maximal width of the current animation
            int getH() { return cur->h; } ///< Retrieve the maximal height of the current animation
        //@}
        
        /// @name Rendering functions
        //@{
            void draw(BITMAP *dest, int xpos,int ypos);
            void draw_lit(BITMAP *dest, int xpos,int ypos, int tint);
        //@}
        
    friend class cmAnim;
};

/// Master class for animations
class cmAnim : public cDataSystem {
    private:
        std::list<cAnimation*> data;
        
        typedef std::list<cAnimation*>::iterator AnimIter;
	public:
        cmAnim()
        { animData = new cmAnimData; }
        
		/// @name Creation of new animations
		//@{
            class cAnimation *add(std::string);
            class cAnimation *add(cAnimData *);
		//@}
		
		/// @name Overloaded functions
		//@{
            void init(void) 
            { }
            
            void level_init(void) {}
            int load(void);
            
            void process(double);
            void draw(void) {}
            void clear_data(void);
        //@}
        
        cmAnimData *animData;
};

#endif

