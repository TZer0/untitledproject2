/**
 * File: timer.cpp
 *
 * Description:	Timer module, handles portable timing.
 *
 */
// Other includes
#include "timer.h"
#include "../port.h" // For allegro

#if defined(unix) || defined(__unix__) || defined(__unix)
	#include <unistd.h>
#endif

#if (_POSIX_VERSION) >= 200112L || (BSD) // Which supports gettimeofday()
	#include <sys/time.h>
	
	struct timeval curTime;
	struct timeval prevTime;
	struct timezone timeZ;
	double __timer_delta;
	double __frame_time;
	double __fps_timer;
	
	void timer_init() {
		timeZ.tz_minuteswest = 0;
		timeZ.tz_dsttime = 0;
	}
	
	void setTimer() {
		gettimeofday(&prevTime, &timeZ);
	}

	bool newFrame() {
		gettimeofday(&curTime, &timeZ);
		if(curTime.tv_usec > prevTime.tv_usec) {
			__timer_delta = double(curTime.tv_usec-prevTime.tv_usec)/double(1.0e6); // Microsec timer
		}else {
			__timer_delta = double((1.0e6+curTime.tv_usec)-prevTime.tv_usec)/double(1.0e6); // Microsec timer
		}
		
		if(__timer_delta > 1.0/double(TIMER_SPEED)) return true;
		else return false;
	}
	
	double getDelta() {
		__frame_time = __timer_delta;
		newFrame();
		prevTime.tv_usec = curTime.tv_usec;
		
		return __timer_delta;
	}
	
	double getFps(double delta) {
	    
	    return 1.0/delta;
	}
#else
    volatile int timer = 0;
    volatile int fps_timer = 0;
    volatile int fps_var = 0;
    void set_timer(void) { timer++; } END_OF_FUNCTION(set_timer);
    
    bool once = true;
    
    void timer_init() {
        LOCK_FUNCTION(set_timer);
        LOCK_VARIABLE(timer);
        install_int_ex(set_timer, BPS_TO_TIMER(TIMER_SPEED)); // 100 Hz, the timer is primarily used for animation and such anyway.
    }
    
    void setTimer() {
        timer = 0;
    }
    
    bool newFrame() {
        return(timer>0);
    }
    
    double getDelta() {
        double delta = double(timer)/TIMER_SPEED;
        timer = 0;
        return(delta);
    }
    
    double getFps(double delta) {
        if(once) {
            //LOGC(LWARN, "FPS timer not available on platform");
            once = false;
        }
        return 0.0;
    }
#endif


// Class functions
/**
 * Initializes the timer
 */
int cmTimer::init()
{
    timer_init();
    return 1;
}

/**
 * Returns the timer value
 */
int cmTimer::get_timer(void)
{
    if(newFrame()) {
        delta_var = getDelta();
        return 1;
    }else
        return 0;
}

/**
 * Resets the timer to zero, and sets last_timer for the delta function
 */
void cmTimer::reset_timer(void)
{
    getDelta();
}

/**
 * Computes the delta since the last call to the function
 * @returns The delta time in seconds
 */
double cmTimer::delta(void)
{
    return delta_var;
}

/**
 * Returns the number of seconds the program has been running
 */
double cmTimer::get_ptime(void)
{
	return(double(clock())/double(CLOCKS_PER_SEC));
}

/**
 * Returns the number of frames per second
 */
double cmTimer::fps()
{
	return getFps(delta_var);
}
