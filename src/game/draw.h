/**
 * File: draw.h
 *
 * Description:	Header file for the drawing module
 *
 * (c)2009, by Raymond Loeberg
 */
#ifndef DRAW_H
#define DRAW_H
// Global includes
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// Other includes
#include "game.h"
#include "misc/vector.h"

// Shorthand macros to the camera functions
#define WTOS_X mDraw.wtos_x
#define WTOS_Y mDraw.wtos_y
#define STOW_X mDraw.stow_x
#define STOW_Y mDraw.stow_y
#define ITOW_X mDraw.itow_x
#define ITOW_Y mDraw.itow_y

#define WTOS mDraw.wtos
#define STOW mDraw.stow
#define ITOW mDraw.itow

/**
 * Drawing module.
 * Contains the graphics buffer
 */
class cmDraw {
    private:
		ALLEGRO_DISPLAY *screen;
    public:
        // Initializes the graphics module
        int init();
        int gl_init();
        
        // Other drawing stuff
        // Mostly allegro 4 portability
        ALLEGRO_FONT *font;
        
        // Switching between different camera modes
        void ortho_cam(bool isIntf=false);	///< Orthogonal rendering
        void intf_cam();	///< Interface rendering
        void persp_cam();	///< Perspective rendering
        
        void new_frame(bool clear);
        
        // Camera subsystem
        double cx,cy,zoom;
        
        void set_cam(double x,double y)
            {cx=x; cy=y;}
		void set_zoom(double z)
			{zoom=z;}
        
        int wtos_x(int x) { return (x-cx); }
        int wtos_y(int y) { return (y-cy); }
        
        double stow_x(int x) { return (x+cx); }
        double stow_y(int y) { return (y+cy); }
        
        cVector wtos(cVector v)
            { return(cVector(v.x-cx, v.y-cy)); }
        cVector stow(cVector v)
            { return(cVector(v.x+cx, v.y+cy)); }
};

extern class cmDraw mDraw;

#endif 
