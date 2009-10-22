/**
 * File: input.cpp
 *
 * Description:	Module to store input data [keyboard and mouse] into arrays
 *              of flags for just pressed/released keys/mousebuttons.
 *
 * (c)2009, by Raymond Loeberg
 */
// Global includes
#include <allegro.h>

// Other includes
#include "input.h"

void cmInput::update(void)
{
	int k;
	poll_mouse();
	poll_keyboard();
	
	// Update mouse state
		// A mouse button is pressed when the previous state was not set and the current state is set
		mouse_pb = mouse_b & (~mouse_old);
		
		// A mouse button is released when the previous state was set and the current state is not set
		mouse_rb = (~mouse_b) & mouse_old;
	
	// Same goes for keys
	mouse_old = mouse_b;
	for(k=0;k<KEY_MAX;k++) {
		if(!key_old[k] && key[k]) pkey[k] = key[k];
		else pkey[k] = 0;
		
		if(!key[k] && key_old[k]) rkey[k] = key[k];
		else rkey[k] = 0;
		
		key_old[k] = key[k];
	}
}
