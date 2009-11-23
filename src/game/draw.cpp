/**
* File: draw.cpp
*
* Description: Draw module functions
*/
#include "draw.h"
#include "game.h"
#include "level/level.h"

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

void cmDraw::cam_cap(void)
{
    if(cx<0.0) cx = 0.0;
    if(cy<0.0) cy = 0.0;
    int width  = mGame->mLevel->get_sizex()*32 - SCREEN_W; 
    int height = mGame->mLevel->get_sizey()*32 - SCREEN_H; 
    if(cx > width)  cx = width;
    if(cy > height) cy = height;
}