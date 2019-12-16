#include "renderlinux.h"
#include <iostream>
#include <SDL.h>
#define dbl long double

using namespace std;

extern Screen s;


    
    void Screen::clear()
    {   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 15);
        SDL_RenderClear(renderer);
    }
    void Screen::put_pixel(int x, int y,  unsigned char r, unsigned char g, unsigned char b)
    {   
        if(x >0 && x < length && y >0 && y<height)
        {   SDL_SetRenderDrawColor(renderer, r, g, b, 15);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    void Screen::put_pixel_3(dbl x, dbl y)
   {   
    if (x >0 && x < length && y >0 && y<height)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 15);
        SDL_RenderDrawPoint(renderer, x, y);
        
    }
    }

    void Screen::Draw()
    {   SDL_Delay(200/25);
 
        SDL_RenderPresent(renderer);
        SDL_Event windowEvent;
        
         if(SDL_PollEvent(&windowEvent))
            {
                if(SDL_QUIT == windowEvent.type)
                {   s.~Screen();
                    
                }
            }
        
    }

    Screen::Screen(int l,int h)
    {   cout<<"constructing screen"<<endl;
        SDL_CreateWindowAndRenderer(l,h,SDL_WINDOW_ALLOW_HIGHDPI,&window,&renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        window_surface = SDL_GetWindowSurface(window);
        length = l*10;
        height = h*10;
    }

    Screen::~Screen()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    /*void Screen::cleanup()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }*/   

    
    
    void SetCursorPos(int x,int y)
    {
        SDL_WarpMouseInWindow(s.window,x,y);
    }
