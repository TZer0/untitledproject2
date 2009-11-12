#include "collision.h"
#include "colapply.h"

/**
 * Applies a function on all instances in a collision map in range of a given collision object.
 * Anyone who wants to collide with me should call this function
 *
 * @param col Collision object that will collide
 * @param caller The cApplyCollision object that calls for collision
 */
void cApplyCollision::apply_collision(cApplyCollision *caller, cCollision *col)
{
    // Set who asked for collision
    this->caller = caller;
    
    // Depending on collision type
    switch(col->getType())
    {
        // Point collision tests directly
        case CollisionPoint:
            std::vector<sColSectorInstance*> *clist;
            clist = checkpoint(col->getPos());
            
            if(clist != NULL) {
                iterate_collision(clist);
                
                // Untouch all sector instances
                for(std::vector<sColSectorInstance*>::iterator ci=clist->begin(); ci!=clist->end(); ci++) {
                    (*ci)->hasTouched = false;
                }
            }
        break;
        
        default:
            // Using the collision map checkbox() function
            checkbox(col->getPos() + col->tl, col->getPos() + col->br, this);
    }
}

/**
 * Iterates over all collision objects in a vector
 * and applies the collision_function() to all of them
 */
void cApplyCollision::iterate_collision(std::vector<sColSectorInstance*>*cols)
{
    for(std::vector<sColSectorInstance*>::iterator i=cols->begin(); i!=cols->end(); i++) {
        if(!(*i)->hasTouched) {
            // The rule is: We call our own collision_function, with the associated pointer
            // that is given to the sector in an sColSectorInstance.
            //
            // The collision_function is pretty much required to call test_collision for each
            // collision object that "ptr" contains
            collision_function(caller->getId(), (*i)->ptr);
            (*i)->hasTouched = true;
        }
    }
}
