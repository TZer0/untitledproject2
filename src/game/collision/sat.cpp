/**
 * \file sat.cpp
 *
 * Description: Processes the (lightning fast) separating axis theorem for our collision objects
 *
 * (c)2009 by Raymond Loeberg
 */
#include "collision.h"

#include <limits>
#define inf std::numeric_limits<double>::infinity()

/**
 * Main function to check for collision.
 *
 * @return A sColReturn object filled with collision information
 */
sColReturn cCollision::collide(cCollision *target, cVector vel)
{
    sColReturn ret;
    ret.isCol = true; // We assume initially that there is a collision
    
    // Relative distance between the two instances
    cVector off = target->getPos() - getPos();
    
    // Get target's normals
    cVector *targnorm = target->getNormal();
    cVector *targpts = target->getPoint();
    
    double my_min, my_max;
    double th_min, th_max;
    
    double mindist = -inf;
    cVector minn;
    
    // Special case processing for circles (they need to have their normal in order)
    // Ignored for now
    if(type == CollisionCircle)
        ;
    
    if(target->getType() == CollisionCircle)
        ;
    
    // Loop through all axises of self and target
    cVector n;
    for(int ax=0;ax < type+target->getType(); ax++) {
        // Retrieve normal
        if(ax < type)
            n = normals[ax];
        else
            n = targnorm[ax-type];
        
        // Project me onto the normal
        my_min = my_max = (points[0]+off).dot(n);
        for(int i=1;i<type;i++) {
            double dot = (points[i]+off).dot(n);
            
            if(dot < my_min) my_min = dot;
            if(dot > my_max) my_max = dot;
        }
        
        // Project them onto the normal
        th_min = th_max = targpts[0].dot(n);
        for(int i=1;i<target->getType();i++) {
            double dot = targpts[i].dot(n);
            
            if(dot < th_min) th_min = dot;
            if(dot > th_max) th_max = dot;
        }
        
        // Find intersection amount
        double dist;
        if(th_max < my_min) dist = my_min - th_max;
        else                dist = th_min - my_max;
        
        // This is the wonderful thing about SAT:
        // If there is no collision along one normal, there can't be a collision any other way.
        if(dist >= 0.0) {
            ret.isCol = false;
            break;
        }else {
            // To ensure we escape the way where there is the least collision
            if(dist > mindist) {
                mindist = dist;
                minn = n;
            }
        }
    }
    
    if(ret.isCol) {
        ret.orp.x = minn.x*(-mindist);
        ret.orp.y = minn.y*(-mindist);
    }
    
    return ret;
}
