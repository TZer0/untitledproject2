/**
 * File: draw.cpp
 *
 * Description:	Handles the drawing module.
 *              Supports different drawing types
 *
 * (c)2009, by Raymond Loeberg
 */
// Module includes
#include "draw.h"
#include "editor/editor.h"

#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <GL/glut.h>

class cmDraw mDraw;

/**
 * Initializes the graphics module
 * using the desired graphics processing type
 */
int cmDraw::init()
{
	al_set_new_display_flags(ALLEGRO_OPENGL);
    screen = al_create_display(1024,768);
    
    /// @todo Temporary solution: Load font from disk
    font = al_load_ttf_font("DejaVuSans.ttf", 10, 0);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	glEnable(GL_TEXTURE_2D);
	
	ortho_cam();
	
	zoom = 1.0;
	
    return 0;
}

int cmDraw::gl_init()
{
	return 0;
}

void cmDraw::persp_cam()
{
	// We will always revert to orthogonal cam, when editor is active
	if(mEditor.active) {
		ortho_cam();
		return;
	}
	
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0,0,0,0);
    glClearDepth(1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glDepthFunc(GL_LEQUAL);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, -1024.0/768.0, 0.1, 1e18);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotatef(180,0,0,1);
	glViewport(0,0,1024,768);
	glTranslatef(-1024/2,-768/2,-(1024+768.0)/2.0*(1.0/zoom));
}

void cmDraw::ortho_cam(bool isIntf)
{
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(isIntf)
		glOrtho(0,1024,768,0, 0.01, 1e18);
	else
		glOrtho(0,1024*zoom, 768*zoom, 0, 0.01, 1e18);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glViewport(0,0,1024,768);
	glTranslatef(0,0,1);
}

void cmDraw::intf_cam()
{
	ortho_cam(true);
}

/**
 * Moves on to a new frame
 */
void cmDraw::new_frame(bool clear)
{
	al_flip_display();
	
	persp_cam();
	if(clear)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
