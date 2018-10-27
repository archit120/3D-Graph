//defines 3d vectors, camera and triangles (which form the mesh)
//AUTHOR: ShreyanshDarshan

#pragma once
#include<cmath>
#include"Vector3D.h"
#define dbl long double

class Triangle
{
public:
	Vector3D actual[3];
	Vector3D projected[3];
	Vector3D normal;

	dbl CalculateNormal();
	void VertexToTriangle(Vector3D** vertex, int x, int y, int type);
};






