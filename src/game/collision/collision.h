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
class cColMap;

/// Enums

/// Possible collision types.
/// The number determines the number of points/normals
enum CollisionType {
    CollisionPoint = 0,
    CollisionRectangle = 4,
    CollisionTriangle = 3,
    CollisionCircle = 1,
};

/// Subclasses
    /// Information about a collision
    struct sColReturn {
        bool isCol;         ///< Flag if there is a collision
        cVector orp;        ///< The path to move to escape collision (original return path)
    };
    
    /// Collision class
    class cCollision {
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
            cCollision(cVector *pos, cVector offset, double radius)     ///< Constructor for a circle collision
                    { cCollision(pos, offset, radius, 0.0, CollisionCircle); }
            cCollision(cVector *pos, cVector offset,
                        double w,double h, CollisionType type);         ///< Constructor for a rectangle/triangle collision
            
            bool detect(cCollision *target);                            ///< Detects collision
            sColReturn collide(cCollision *target, cVector vel);        ///< As above, but also sets a return path into a sColReturn instance
            
            /// Returns our type
            CollisionType getType() { return type; }
            
            /// Returns out position
            cVector getPos() { return *pos; }
            
            cVector *getNormal() { return normals; }
            cVector *getPoint() { return points; }
            
            /// The extremes of this collision instance
            cVector tl,br;
            
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
        
        /// Overloaded functions from cDataSystem
        void init(void) {}
        void level_init(void) {}
        int load(void) { return 0; }
        void process(double delta) {}
        void draw(void) {}
        void clear_data(void) {}
        
};

/// Function declarations

#endif

