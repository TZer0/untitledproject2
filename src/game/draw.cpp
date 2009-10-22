/**
* File: draw.cpp
*
* Description: Draw module functions
*/
#include "draw.h"

void cmDraw::init(void)
{
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
}

void cmDraw::draw(void)
{
    blit(buffer,screen,0,0,0,0,buffer->w,buffer->h);
    clear_bitmap(buffer);
}

