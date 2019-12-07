//defines 3d vectors, camera and triangles (which form the mesh)
//AUTHOR: ShreyanshDarshan, archit120

#pragma once
#include<cmath>
#include"Vector3D.h"
#include"Vector2D.h"
#define dbl long double

class Triangle
{
public:
	Vector3D actual[3];
	Vector2D projected[3];

	dbl CalculateNormal(); //Implement @Neha Dalmia
};






