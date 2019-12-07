#include "stdafx.h"
#include "MainLoop.h"
#include <cmath>

#define dbl long double
#define sizex 1000
#define sizey 1000

/*
	Represents the function to be plotted by returning the z value. The variables y and x correspond to input coordinates. A third variable t is for interactive plots.
*/
dbl function(dbl y, dbl x, dbl t)
{
	return sin(sqrt((x) * (x)+(y) * (y)));
}

void MainLoop::loop(Screen& s, Camera& ca)
{
	double t = 0;
	while (true)
	{
		t += 0.1;
		s.clear();
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
		for (double x = -100; x < 100; x += 0.1)
		{
			for (double y = -100; y < 100; y += 0.1)
			{
				dbl z = function(y, x, -t);
				//cout << z << "\n";
				auto o = ca.WorldToScreen(Vector3D(x, y, z));
				//cout << o.X << " " << o.Y << " " << o.Z<< "\n";
				s.put_pixel_3(o.X + sizex / 2, o.Y + sizey / 2);
			}
		}

		//int count = 0;
		//for (int y = 1; y < 1000 - 1; y += 1)
		//{
		//	for (int x = 0; x < 1000-1; x += 1)
		//	{
		//		mesh[count].VertexToTriangle(onScreen, x, y, 1);
		//		count++;
		//		mesh[count].VertexToTriangle(onScreen, x, y, 0);
		//		count++;
		//	}
		//}
		//for (int x = 0; x < 1000 - 1; x += 1)
		//{
		//	mesh[count].VertexToTriangle(onScreen, x, 0, 1);
		//	count++;
		//	mesh[count].VertexToTriangle(onScreen, x, 1000 - 1, 0);
		//	count++;
		//}

		s.Draw();
		//..cout << "render" << "\n";
		//cout << ca.Location.X << " " << ca.Location.Y << " " << ca.Location.Z << "\n";
		//cout << ca.Normal.X << " " << ca.Normal.Y << " " << ca.Normal.Z << "\n";
		//_getch();
		//s.clear();
	}
}