// 3D Graph.cpp : Defines the entry point for the console application.
//AUTHOR: archit120 + ShreyanshDarshan
#ifdef _WIN32
	#include "stdafx.h"	
	#include "render.h"
	#include <conio.h>
#elif __APPLE__||__linux__
	#include "renderlinux.h"
#endif
#include <iostream>
#include <vector>
#include "ControlLoop.h"
#include "Triangle.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Vector2D.h"

#define dbl long double
#define sizex 1000
#define sizey 1000

using namespace std;

/*
	Represents the function to be plotted by returning the z value. The variables y and x correspond to input coordinates. A third variable t is for interactive plots.
*/
dbl mathFunction(dbl y, dbl x, dbl t)
{
	return sin(sqrt((x) * (x)+(y) * (y)));
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
	Screen s(sizex, sizey);
	cin.get();
	SetCursorPos(sizex/2, sizey/2);
	
	double t = 0;
	while (true)
	{
		s.clear();

		ControlLoop::loop(ca, t);

		for (double x = -100; x < 100; x += 0.1)
		{
			for (double y = -100; y < 100; y += 0.1)
			{
				dbl z = mathFunction(y, x, -t);
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

	cin.get();
    return 0;
}

