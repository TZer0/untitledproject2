/**
 * File: input.h
 *
 * Description:	Header file for input.cpp
 *
 * (c)2009, by Raymond Loeberg
 */
#ifndef INPUT_H
#define INPUT_H
#include "../port.h"

/// Stores pressed/released keys/mousebuttons and updates them on request
class cmInput {
	public:
		void update(void);
		
		/// Is only true when a given key is hit 
		char pkey[KEY_MAX];
		
		/// Is only true when a given key is released
		char rkey[KEY_MAX];
		
		/// Is set when a mouse button is pressed
		int mouse_pb;
		
		/// Is set when a mouse button is released
		int mouse_rb;
		
	private:
		int mouse_old;
		char key_old[KEY_MAX];
};

#endif
