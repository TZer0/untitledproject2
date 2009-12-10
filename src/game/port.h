#if !defined(WIN32) && !defined(WIN64) && !defined(_MSC_VER)
#include <allegro.h>
#else
#include "allegro.h"
#include "winalleg.h"
#define _USE_MATH_DEFINES
#endif

