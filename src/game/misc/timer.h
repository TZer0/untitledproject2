/**
 * File: timer.h
 *
 * Description:	Header for the timer module
 */
#ifndef TIMER_H
#define TIMER_H
// Global includes
#include <time.h>

#define TIMER_SPEED 100

/// Timer module. Handles timer related stuff
class cmTimer {
    private:
        double delta_var;
    public:
        int init(); // Begins a timer
        int get_timer(); // Returns the current timer position
        void reset_timer(); // Sets the timer back to zero
        double delta(); // Returns the time taken since the last call to delta()
        
        // Other functions
        double get_ptime(); // Returns the program elapsed time in seconds (NOTE: Cross platform?)
        double fps();	// Returns the frames processed per second
        
        double cfps;
        int last_timer; // Set after each call to delta()
};

#endif 
