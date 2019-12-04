// 3D Graph.cpp : Defines the entry point for the console application.
//AUTHOR: archit120 + ShreyanshDarshan

#include "stdafx.h"

#include "render.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <conio.h>
#include "Triangle.h"
#include "Camera.h"
#include "Vector3D.h"

#define dbl long double
#define sizex 1000
#define sizey 1000

using namespace std;

/*
	Represents the function to be plotted by returning the z value. The variables y and x correspond to input coordinates. A third variable t is for interactive plots.
*/
dbl function(dbl y, dbl x, dbl t)
{
	return sin(sqrt((x) * (x)+(y) * (y)));
	//if(y < 50 && x < 50)
	//return sin(sqrt((x +25)*(x +25) + (y - 10)*(y - 10)) + t)  + sin(sqrt((x+25)*(x+25) + (y +10)*(y +10)) + 2*t);
	//return sqrt(y*x);
	//return 0;
}

int main()
{
	/*Vector3D** onScreen = new Vector3D* [1000];
	Triangle* mesh;
	mesh = new Triangle [2 * (1000 - 1)*(1000 - 1)];
	for (int i = 0; i < 1000; i++)
	{
		onScreen[i] = new Vector3D [1000];
	}*/
	Camera ca(Vector3D(10, 10, 10), 290);
	ca.Location = Vector3D(305, 0, 4);
	//ca.Normal = Vector3D(-1, 0, 0);
	ca.yAxis = Vector3D(0, 0, 1);
	ca.xAxis = Vector3D(0, 1, 0);
	ca.Normal = ca.yAxis.crossProduct(ca.xAxis);
	Screen s(1000, 1000);
	_getch();
	SetCursorPos(500, 500);
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

		if (p.x != 500)
		{
			ca.rotateNormalX(-0.001 * (p.x - 500));
			p.x = 500;
		}
		if (p.y != 500)
		{
			ca.rotateNormalY(-0.001 * (p.y - 500));
			p.y = 500;
		}

		SetCursorPos(p.x, p.y);
		for (double x = -50; x < 50; x+=0.1)
		{
			for (double y = -50; y < 50; y+=0.1)
			{
				dbl z = function(y, x,-t);
				//cout << z << "\n";
				auto o = ca.WorldToScreen(Vector3D(x, y, z));
				//cout << o.X << " " << o.Y << " " << o.Z<< "\n";
				s.put_pixel_3(o.X+ 500, o.Y + 500);
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
	_getch();
    return 0;
}

