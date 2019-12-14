#pragma once
#include <iostream>
#include <SDL.h>
#define dbl long double
using namespace std;

class Screen
{
    public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *window_surface; 
    int length;
    int height;

    inline double dist(double x1, double x2, double y1, double y2)
    {
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    }

    
    
    void clear();
    void put_pixel(int x, int y,  unsigned char r, unsigned char g, unsigned char b);
    void put_pixel_3(dbl x, dbl y);


    void Draw();
    void cleanup();
    Screen(int l,int h);
    


};



void SetCursorPos(int x,int y);