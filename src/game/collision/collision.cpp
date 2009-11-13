/**
 * \file collision.cpp
 *
 * Description: Source file for cmCollision
 *
 * (c)2009 by Raymond Loeberg
 */
#include "collision.h"

/**
 * Creates a cCollision instance
 * @param type Type of collision object to create
 * @param pos Pointer to the position vector to attach the cCollision instance to
 * @param off Relative offset from \p pos the cCollision instance is
 * @param argX Arguments to create the collision instance
 */
cCollision *cmCollision::create(CollisionType type, cVector *pos, cVector off, double arg1, double arg2)
{
    cCollision *tmp;
    
    switch(type)
    {
        case CollisionPoint:
            tmp = new cCollision(pos, off);
        break;
        
        case CollisionRectangle:
        case CollisionTriangle:
            tmp = new cCollision(pos, off, arg1, arg2, type);
        break;
        
        case CollisionCircle:
            tmp = new cCollision(pos, off, arg1);
        break;
    }
    
    data.push_back(tmp);
    
    return tmp;
}

/**
 * Create a point collision instance
 */
cCollision::cCollision(cVector *pos, cVector off) : pos(pos), offset(off), type(CollisionPoint)
{
    toDie = false;
    normals = NULL;
    points = new cVector;
    *points = off;
}

/**
 * Create a rectangle/triangle instance
 */
cCollision::cCollision(cVector *pos, cVector off, double w, double h, CollisionType t) : pos(pos), offset(off), type(t)
{
    toDie = false;
    
    int vertexc = type;
    
    normals = new cVector[vertexc];
    points = new cVector[vertexc];
    
    switch(type) {
        case CollisionRectangle:
            points[0] = cVector(0,0)+off;
            points[1] = cVector(w,0)+off;
            points[2] = cVector(w,h)+off;
            points[3] = cVector(0,h)+off;
        break;
        
        case CollisionTriangle:
            points[0] = cVector(0,0)+off;
            points[1] = cVector(w,0)+off;
            points[2] = cVector(w,h)+off;
        break;
        
        case CollisionCircle:
            points[0] = cVector(w,0)+off;
        break;
        
        case CollisionPoint:
        break;
    }
    
    if(type != CollisionCircle) {
        tl.x = (0<w ? 0:w) + off.x;
        tl.y = (0<h ? 0:h) + off.y;
        br.x = (0<w ? w:0) + off.x;
        br.y = (0<h ? h:0) + off.y;
    }
    
    generate_normals();
}

#include <stdio.h>
/**
 * Generates the collision normals for the object
 */
void cCollision::generate_normals()
{
    for(int i=0;i<type-1;i++) {
        normals[i] = points[i+1]-points[i];
    }
    
    // Last normal points back to the first
    normals[type-1] = points[0]-points[type-1];
    
    for(int i=0;i<type;i++) {
        normals[i] = -(normals[i].normal()).norm();
    }
    
    
    if(type == CollisionTriangle)
        normals[0] = -normals[0];
}


