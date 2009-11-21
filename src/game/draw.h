/**
* File: draw.h
*
* Description: Header file for cmDraw
*/
#ifndef DRAW_H
#define DRAW_H
#include "port.h"
#include "misc/vector.h"

// Shorthand macros to the camera functions
#define WTOS_X mGame->mDraw->wtos_x
#define WTOS_Y mGame->mDraw->wtos_y
#define STOW_X mGame->mDraw->stow_x
#define STOW_Y mGame->mDraw->stow_y

#define WTOS mGame->mDraw->wtos     // World to screen coordinates
#define STOW mGame->mDraw->stow       // Screen to world coordinates

class cmDraw {
    private:
        // Camera coordinates
        double cx,cy;
    
    public:
        cmDraw()
        { cx=cy=0.0; }
        
        BITMAP *buffer;
        void init(void);
        void draw(void);
        
        void set_cam(double x,double y) {cx=x; cy=y;}

        // I (Stian) include this functoin as it actually will be handy 
        // for more advanced camera control. Have a look in player.cpp
        // to see what I mean.
        cVector get_cam(){ return cVector(cx, cy); }
        
        int wtos_x(double x) { return(int(x-cx)); }
        int wtos_y(double y) { return(int(y-cy)); }

        // Ahem, (cough cough), I'll pretend I (Stian) didn't see this..
        int htonz(int h) {
            return 3;
        }
        
        double stow_x(int x) { return(x+cx); }
        double stow_y(int y) { return(y+cy); }
        
        cVector wtos(cVector v)
            { return(cVector(v.x-cx, v.y-cy)); }
        cVector stow(cVector v)
            { return(cVector(v.x+cx, v.y+cy)); }
        
        void cam_cap() {
            if(cx<0.0) cx = 0.0;
            if(cy<0.0) cy = 0.0;
            if(cx > SCREEN_W) cx = SCREEN_W;
            if(cy > SCREEN_H) cy = SCREEN_H;
        }
};

#endif

