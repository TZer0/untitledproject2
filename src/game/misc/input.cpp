/**
 * File: input.cpp
 *
 * Description:	Module to store input data [keyboard and mouse] into arrays
 *              of flags for just pressed/released keys/mousebuttons.
 *
 * (c)2009, by Raymond Loeberg
 */
// Global includes
#include <string.h>

// Other includes
#include "input.h"
#include "log.h"

class cmInput mIn;

/// Attaches mouse and keyboard handles to the event queue
void cmInput::init(void)
{
	events = al_create_event_queue();
	LOGS(LDEBUG, "Events queue is %p", events);
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_mouse_event_source());
	
	// Clear keybuffer
	memset(key,0,sizeof(char)*ALLEGRO_KEY_MAX);
	
	mouse_b = 0;
	mIn.mouse_x = mIn.mouse_y = mouse_z = 0;
	m_scr = 0;
}

void cmInput::update(void)
{
	ALLEGRO_EVENT ev;
	
	// Empty just-pressed and just-released buffers
	for(int k=0;k<ALLEGRO_KEY_MAX;k++) {
		pkey[k] = 0;
		rkey[k] = 0;
	}
	
	// Empty pressed/released mouse buttons
	mouse_pb = 0;
	mouse_rb = 0;
	
	keyrep = 0;
	
	// Get events from event-handler
	if(!al_event_queue_is_empty(events)) {
		while(al_get_next_event(events, &ev)) {
			int ki = ev.keyboard.keycode;
			switch(ev.type) {
				case ALLEGRO_EVENT_KEY_DOWN:
					pkey[ki] = 1;
					key[ki] = 1;
					
					keyrep = (ki<<8) | (ev.keyboard.unichar & 0xff);
				break;
				
				case ALLEGRO_EVENT_KEY_UP:
					rkey[ki] = 1;
					key[ki] = 0;
				break;
				
				case ALLEGRO_EVENT_MOUSE_AXES:
					mIn.mouse_x = ev.mouse.x;
					mIn.mouse_y = ev.mouse.y;
					
					m_scr = ev.mouse.dz;
				break;
				
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					mouse_b |= 1<<(ev.mouse.button-1);
					mouse_pb |= 1<<(ev.mouse.button-1);
				break;
				
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
					// Mask out the mouse button
					// This "should" work
					mouse_b &= ~(1<<(ev.mouse.button-1));
					mouse_rb |= 1<<(ev.mouse.button-1);
				break;
			}
		}
	}
}
