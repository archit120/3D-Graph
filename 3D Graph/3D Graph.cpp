// 3D Graph.cpp : Defines the entry point for the console application.
//AUTHOR: archit120 + ShreyanshDarshan

#include "stdafx.h"

#include "render.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include "Triangle.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "MainLoop.h"
#define dbl long double
#define sizex 1000
#define sizey 1000

using namespace std;

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
	_getch();
	SetCursorPos(sizex/2, sizey/2);
	
	MainLoop::loop(s, ca);

	_getch();
    return 0;
}

