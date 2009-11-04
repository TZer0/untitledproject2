/**
 * \file colapply.h
 *
 * Description: Header file for the collision interaction system
 *
 */
#ifndef COLAPPLY_H
#define COLAPPLY_H
// Other includes
#include "colmap.h"

// Forward declaration of classes
class cCollision;

/**
 * Class to derive for handling collision against a
 * collision map.
 *
 * This class derives from the collision map, and utilizes it heavily
 * for determining which instances to collide with
 */
class cApplyCollision : cColMap {
    private:
        /// All cApplyCollision instances keeps an identifier
        /// to be used when identifying which modules interact with
        /// each other
        int id;
        
        /// The cApplyCollision that called us for a collision
        cApplyCollision *caller;
        
        /// The collision object that called us for collision
        cCollision *col;
        
        /// Function that iterates through a list of collision map objects
        void iterate_collision(std::vector<sColSectorInstance*>*cols);
    public:
        cApplyCollision(int id, int depth, double w,double h) : cColMap(depth,w,h), id(id)
            { }
        
        int getId() { return id; }
        
        /// Resizes the collision map
        void resize_colmap(double w,double h) { resize(w,h); }
        
        /// Function to apply collision onto a collision map
        void apply_collision(cApplyCollision *caller, cCollision *col);
        
        /// Overloadable function that is called when an external
        /// module is colliding with this module
        ///
        /// @param caller_id The module that called for collision with us
        virtual void collision_function(int caller_id, void* inst)=0;
        
        /// Overloadable function that is called for each collision map
        /// intersection. This function has to test if it collides with col,
        /// and return true or false depending on whether it does or not
        ///
        /// @param dial_id The module ID we're testing against
        /// @param col The collision block that we have to test against
        virtual bool test_collision(int dial_id, cCollision *col);
        
        // We're friends with the colmap function that applies onto a function
        friend class cColMap;
};

#endif
