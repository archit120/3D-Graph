//defines 3d vectors, camera and triangles (which form the mesh)
//AUTHOR: ShreyanshDarshan, archit120

#pragma once
#include<cmath>
#include <Eigen/Dense>
#define dbl long double

using namespace Eigen;

/*
	Create a class for storing triangles and creating new ones with given coordinates
*/
class Triangle
{
public:
	Vector3d actual[3];
	Vector2d projected[3];

	dbl CalculateNormal(); //Implement @Neha Dalmia
};






