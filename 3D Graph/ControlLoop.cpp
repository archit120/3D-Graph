#ifdef __APPLE__||__linux__
	#include <SDL.h>
	#include "renderlinux.h"
	struct POINT
	{
		int x,y;
	};

	void GetCursorPos(POINT *p)
	{	int x,y;
		SDL_GetMouseState(&x, &y);
		p->x=x;
		p->y=y;
	}

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
SDL_Event event; 
char _getch(void)
{	
	if(event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			return 'w';
			/* code */
			break;
		case SDLK_a:
			return 'a';
			break;
		case SDLK_s:
			return 's';
			break;
		case SDLK_d:
			return 'd';
		default:
			return 'z'; 
			break;
		}
	}
}

int _kbhit()
{
	SDL_PollEvent(&event);
	if(event.type == SDL_KEYDOWN)
		return 1;
	else
	{
		return 0;
	}
	
}

#endif
#include "ControlLoop.h"
#include <cmath>

#define dbl long double
#define sizex 1000
#define sizey 1000

void ControlLoop::loop(Camera& ca, double& t)
{
	t += 0.1;
		
	ControlLoop::UserInput(ca);

	POINT p;
	GetCursorPos(&p);

	if (p.x != sizex / 2)
	{
		ca.rotateNormalX(-0.001 * (p.x - sizex / 2));
		p.x = sizex / 2;
	}
	if (p.y != sizey / 2)
	{
		ca.rotateNormalY(-0.001 * (p.y - sizey / 2));
		p.y = sizey / 2;
	}

SetCursorPos(p.x, p.y);
}

void ControlLoop::UserInput(Camera& ca)
{
	if (_kbhit())
	{
		char c;
		c = _getch();

		switch (c)
		{
		case 'w':
			ca.Location = ca.Location + ca.Normal;
			break;
		case 's':
			ca.Location = ca.Location - ca.Normal;
			break;
		case 'a':
			ca.Location = ca.Location - ca.xAxis;
			break;
		case 'd':
			ca.Location = ca.Location + ca.xAxis;
			break;

		case 't':
			ca.Location = ca.Location + ca.yAxis;
			break;
		case 'g':
			ca.Location = ca.Location - ca.yAxis;
			break;
		case 'q':
			ca.rotateAxis(0.1);
			break;
		case 'e':
			ca.rotateAxis(-0.1);
			break;
		case 'y':
			ca.rotateNormalX(0.01);
			break;
		case 'h':
			ca.rotateNormalX(-0.01);
			break;
		case 'u':
			ca.rotateNormalY(0.01);
			break;
		case 'j':
			ca.rotateNormalY(-0.01);
			break;
		}
	}
}
