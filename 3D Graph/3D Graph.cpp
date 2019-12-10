// 3D Graph.cpp : Defines the entry point for the console application.
//AUTHOR: archit120 + ShreyanshDarshan

#include "stdafx.h"

#include "render.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include "Triangle.h"
#include "Camera.h"
#include <Eigen/Dense>

#include "ControlLoop.h"
#define dbl long double
#define sizex 1000
#define sizey 1000

using namespace Eigen;
using namespace std;
/*
	Represents the function to be plotted by returning the z value. The variables y and x correspond to input coordinates. A third variable t is for interactive plots.
*/
dbl plt_func(dbl y, dbl x, dbl t)
{
	return sin(sqrt((x) * (x)+(y) * (y)));
}
/*
	The main function containing the running code
*/
int main()
{
	/*Vector3d** onScreen = new Vector3d* [1000];
	Triangle* mesh;
	mesh = new Triangle [2 * (1000 - 1)*(1000 - 1)];
	for (int i = 0; i < 1000; i++)
	{
		onScreen[i] = new Vector3d [1000];
	}*/

	Camera ca(Vector3d(10, 10, 10), 290);
	ca.Location = Vector3d(305, 0, 4);
	//ca.Normal = Vector3d(-1, 0, 0);
	ca.yAxis = Vector3d(0, 0, 1);
	ca.xAxis = Vector3d(0, 1, 0);
	ca.Normal = ca.yAxis.cross(ca.xAxis);
	Screen s(sizex, sizey);
	_getch();
	SetCursorPos(sizex/2, sizey/2);
	double t = 0;
	while (true)//this is a continuous loop so as to provide continuous input through keyboard and mouse
	{
		s.clear();

		ControlLoop::loop(ca, t);

		//for (double x = -100; x < 100; x += 0.1)
		//{
		//	for (double y = -100; y < 100; y += 0.1)
		//	{
		//		dbl z = plt_func(y, x, -t);
		//		//cout << z << "\n";
		//		auto o = ca.WorldToScreen(Vector3d(x, y, z));
		//		//cout << o.X << " " << o.Y << " " << o.Z<< "\n";
		//		s.put_pixel_3(o[0] + sizex / 2, o[1] + sizey / 2);
		//	}
		//}

		Triangle t;
		t.actual[0] = Vector3d(10, 0, 0);
		t.actual[1] = Vector3d(0, 10, 0);
		t.actual[2] = Vector3d(0, 0, 0);
		auto pt = ca.WorldToScreen(t);
		vector<int> x, y;

		for (auto t : pt)
		x.push_back(t[0] + sizex/2), y.push_back(t[1] + sizey/2);

		s.draw_polygon(x, y, 255, 255, 255);
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
	_getch();//finally
    return 0;
}

