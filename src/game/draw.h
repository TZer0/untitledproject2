/**
* File: draw.h
*
* Description: Header file for cmDraw
*/
#ifndef DRAW_H
#define DRAW_H
#include "port.h"

class cmDraw {
    public:
        BITMAP *buffer;
        void init(void);
        void draw(void);
};

#endif
