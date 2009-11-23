// Global includes
#if !defined(WIN32) && !defined(WIN64) && !defined(_MSC_VER)
#include <math.h>
#else
#define _USE_MATH_DEFINES
#endif
// Other includes
#include "vector.h"

/**
 * Normalizing the input vector, using a fast, but approximate, algorithm.
 *
 * Source: Wikipedia
 */
cVector cVector::snorm(void)
{
	union {
	    int tmp;
	    float val;
	} u;
	u.val = (x*x+y*y);
	u.tmp -= 1<<23;
	u.tmp >>= 1;
	u.tmp += 1<<29;
	
	return(cVector(x/u.val,y/u.val));
}

/**
 * Rotating the target vector to the position of this vector.
 * Rotates it so that the vector is rotated to a different vector
 */
cVector cVector::rotatenorm(const cVector &b)
{
	cVector tmp;
	
	// Angle of this vector
	double ang = atan2(-y,x);
	
	// Rotate the vector
	tmp.x = cos(ang)*b.x+sin(ang)*b.y;
	tmp.y = (-sin(ang)*b.x+cos(ang)*b.y);
	return(tmp);
}

/**
 * Rotating the target vector to the position of this vector.
 * Rotates it so that the vector is normal to the in-vector
 */
cVector cVector::rot(const cVector &b)
{
	cVector tmp;
	
	// Angle of this vector
	double ang = atan2(-y,x)-M_PI/2.0;
	
	// Speed optimization:
	// storing the cos and sin varaibles in temporary space.
	// Deriving sin from cos, using sqrt(), which is faster
	double cosv = cos(ang);
	double sinv = sqrt(1.0-cosv*cosv);
	
	// Rotate the vector
	tmp.x = cosv*b.x-sinv*b.y;
	tmp.y = sinv*b.x+cosv*b.y;
	return(tmp);
}

/**
 * Reverts a previous rotation
 */
cVector cVector::unrot(const cVector &b)
{
	cVector tmp;
	
	// Angle of this vector
	double ang = atan2(-y,x)-M_PI/2.0;
	
	// See note for rot()
	double cosv = cos(ang);
	double sinv =-sqrt(1.0-cosv*cosv);
	
	// Rotate the vector
	tmp.x = cosv*b.x-sinv*b.y;
	tmp.y = sinv*b.x+cosv*b.y;
	return(tmp);
}

