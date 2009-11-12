/**
 * File: input.h
 *
 * Description:	Header file for input.cpp
 *
 * (c)2009, by Raymond Loeberg
 */
#ifndef INPUT_H
#define INPUT_H
#include <allegro5/allegro5.h>

/// Stores pressed/released keys/mousebuttons and updates them on request
class cmInput {
	public:
		void init();
		void update(void);
		
		/// Is only true when a given key is hit 
		char pkey[ALLEGRO_KEY_MAX];
		
		/// Is only true when a given key is released
		char rkey[ALLEGRO_KEY_MAX];
		
		/// Is set when a mouse button is pressed
		int mouse_pb;
		
		/// Is set when a mouse button is released
		int mouse_rb;
		
		/// The relative position (compared to previous poll) of the scroll wheel
		int m_scr;
		
		/// @name Portability stuff
		//@{
			char key[ALLEGRO_KEY_MAX];
			int mouse_x,mouse_y;
			int mouse_b;
			int mouse_z;
			
			int keyrep;
		//@}
	private:
		// Event queue
		ALLEGRO_EVENT_QUEUE *events;
};

extern class cmInput mIn;

#endif
