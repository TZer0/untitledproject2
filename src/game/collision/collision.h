/**
 * \file collision.h
 *
 * Description: Header file for the collision system
 *
 */
#ifndef COLLISION_H
#define COLLISION_H
/// Includes
// Global includes
#include <list>
// Module includes
// Loading includes
// Other includes
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"

/// #Defines
// Typedefs
// Forward declaration of classes

/// Enums
enum CollisionType {
    CollisionPoint,
    CollisionRectangle,
    CollisionTriangle,
    CollisionCircle,
};

/// Subclasses
    /// Information about a collision
    struct sColReturn {
        bool isCol;         ///< Flag if there is a collision
        cVector orp;        ///< The path to move to escape collision (original return path)
    };
    
    /// Collision class
    class cCollsion {
        private:
            cVector *pos;           ///< The position vector we're attached to
            cVector offset;         ///< The offset from the position vector this instance is
            CollisionType type;     ///< What kind of collision object we are
            
            cVector *normals;       ///< Normals generated for the collision object
            cVector *points;        ///< Vector points generated for the collision object
            
            void generate_normals();    ///< Generates collision points and normals for the object
            
            bool toDie;             ///< Flag to determine if this collision objects should be removed from processing
        public:
            cCollision(cVector *pos, cVector offset);                   ///< Constructor for a point collision
            cCollision(cVector *pos, cVector offset, double radius);    ///< Constructor for a circle collision
            cCollision(cVector *pos, cVector offset,
                        double w,double h, CollisionType type);         ///< Constructor for a rectangle/triangle collision
            
            bool detect(cCollision *target);                            ///< Detects collision
            sColReturn collide(cCollision *target, cVector vel);        ///< As above, but also sets a return path into a sColReturn instance
            
            /// Call this function to request destruction of this collision instance
            void eraseMe() { toDie=true; }
    };

/// Module singleton class
class cmCollision : public cDataSystem {
    private:
        /// List of collision instances
        std::list<cCollision*> data;
    public:
        /// Creates a collision instance of the specified type
        cCollision *create(CollisionType type, cVector *pos, cVector offset, double arg1=0.0, double arg2=0.0);        
}

/// Function declarations

#endif
