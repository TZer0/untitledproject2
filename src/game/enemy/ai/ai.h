/**
* File: ai.h
*
* Description: Class declaration for the overloadable AI.
*
*/
#ifndef AI_H
#define AI_H
// Other includes
#include "../../misc/vector.h"

#define AICONSTRUCTOR(name) name(cEnemy *host) : cAI(host) {}

// Forward declarations
class cEnemy;

// Classes
class cAI {
	public:
		cAI(cEnemy *host) : host(host) {}
		
		/// @name: Reactants
		// Reactants are functions that "react" to external events
		//@{
			// Called when the enemy is created
			virtual void onInit(void)=0;
			
			// Called every frame
			virtual void onProcess(double delta)=0;
			
			// Called when colliding with the level
			virtual void onLevelCol(cVector orp)=0;
			
			// Called when hit by a bullet
			virtual void onBulletCol(cVector srcvel, double damage)=0;
			
			// Called when close to the player
			virtual void onPlayerClose(cVector pos, double distance)=0;
		//@}
		
		/// @name: Requests
		// Requests are functions that tests if a certain action is acceptable to do
		//@{
			// Returns true if a jump can be performed with the specific speed, using a specific gravity.
			// The function will perform the jump, and check if it collides with anything on the way
			bool request_jump(cVector vel, double gravity);
			
			// Returns true if a movement of units (pixels) doesn't drop further than heightLimit
			bool request_move(double units, double heightLimit);
			
			// Returns true if there are no obstacles from the enemy's current position to dest
			bool request_flying(cVector dest);
			
			// Returns true if there is a clear path from the enemy's weapon to the destination point.
			bool request_fire(cVector dest);
		//@}
		
		// The enemy that this AI is connected to
		cEnemy *host;
};

#endif
