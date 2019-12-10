#ifdef _WIN32
#include "stdafx.h"
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
		c = cin.get();

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