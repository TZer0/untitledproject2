/**
 * File: vector.h
 *
 * Description:	Header for the vector class.
 *
 * (c)2009, by Raymond Loeberg
 */
#ifndef VECTOR_H
#define VECTOR_H
// Global includes
#include <math.h>

/**
 * Class for vectors.
 *
 * Designed to be used like any other numerical units,
 * but contains some additional functions useful for vectors.
 */
class cVector {
	public:
		cVector() {x=0;y=0;}
		cVector(double x,double y) {this->x = x; this->y = y;}
		cVector(const cVector &b) {x = b.x; y=b.y; }
		
		// Vector assignation
		cVector &operator =(const cVector& b) {x=b.x; y=b.y; return *this;}
		
		// Vector comparison
		// ==: Double equality
		// <=: X (left) equality
		// >=: Y (right) equality
		// !=: Neither equality
		bool operator == (cVector b) {return(x==b.x && y==b.y);}
		bool operator <= (cVector b) {return(x==b.x);}
		bool operator >= (cVector b) {return(y==b.y);}
		bool operator != (cVector b) {return(x!=b.x && y!=b.y);}
		
		// Difference operators
		bool operator <= (double x) {return this->x==x;}
		bool operator >= (double y) {return this->y==y;}
		
		// Vector operations
		// Includes multiplication and division, dot product is own function
		cVector operator + (const cVector &b)    { return(cVector(x+b.x,y+b.y)); }
		cVector operator - (const cVector &b)    { return(cVector(x-b.x,y-b.y)); }
		cVector operator * (const cVector &b)    { return(cVector(x*b.x,y*b.y)); }
		cVector operator / (const cVector &b)    { return(cVector(x/b.x,y/b.y)); }
		cVector operator * (const double &b)     { return(cVector(x*b,y*b)); }
		cVector operator / (const double &b)     { return(cVector(x/b,y/b)); }
		cVector operator - (void)               { return(cVector(-x,-y)); }
		double operator ~ ()                    { return(sqrt(x*x+y*y)); }
		double dot(const cVector &b)             { return(x*b.x+y*b.y); }
		double cross(const cVector &b)           { return(x*b.y-y*b.x); }
		
		/// Normalization of a vector
		cVector norm(void)                      { double len = sqrt(x*x+y*y); return(cVector(x/len,y/len)); }
		
		cVector snorm(void);
		
		/// The line normal to this line, right-handed
		cVector normal(void)                    { return (cVector(-y,x)); }
		//cVector get_negnorm(void);
		
		// Extended vector operations
		void operator += (const cVector &b)  { x+=b.x;y+=b.y; }
		void operator -= (const cVector &b)  { x-=b.x;y-=b.y; }
		void operator *= (const cVector &b)  { x*=b.x;y*=b.y; }
		void operator /= (const cVector &b)  { x/=b.x;y/=b.y; }
		void operator *= (const double &d)   { x*=d;y*=d; }
		void operator /= (const double &d)   { x/=d;y/=d; }
		
		// Special functions
		cVector rotatenorm(const cVector  &b);
		cVector rot(const cVector  &b);
		cVector unrot(const cVector &b);
		cVector swap(void)                  { return(cVector(y,x)); }
		double angle(void)                  { return atan2(-y,x); }
		
		/// Returns a rotation matrix as a cVector.
		/// This matrix can be used by fastrot and fastunrot to point
		/// a vector in the direction of this vector's getrot() matrix.
		/// The new coordinate system is such that this vector's normal points towards [0,1]
		cVector getrot_y() {
            if(y==0 && x==0)
                return cVector(1.0,0.0);
            else {
                cVector t = this->norm();
                return cVector(t.x,t.y);
            }
		}
		
		/// As getrot_y, but rotates the normal point to [1,0]
		cVector getrot_x() {
		    if(y==0 && x==0)
                return cVector(1.0,0.0);
		    else {
		        cVector t = this->norm();
                return cVector(t.x,-t.y);
		    }
		}
		
		/// Applies a fast rotation using a rotation matrix
		void fastrot(const cVector &rot) {
            double tx=x,ty=y;
            x = rot.x*tx - rot.y*ty;
            y = rot.y*tx + rot.x*ty;
        }
        
        /// Applies a fast reversion of a rotation using a rotation matrix
        void fastunrot(const cVector &rot) {
            double tx=x,ty=y;
            x = rot.x*tx + rot.y*ty;
            y =-rot.y*tx + rot.x*ty;
        }
        
        /// Returns a new cVector that has its rotation reversed
        cVector unrotate(const cVector &rot) {
            return(cVector( rot.x*x + rot.y*y,
                           -rot.y*x + rot.x*y ));
        }
		
		double x,y;
};

#endif
