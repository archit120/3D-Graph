//AUTHOR: archit120

#pragma once
#include <vector>
#include"Triangle.h"

#include<Eigen/Dense>
#define dbl long double

using namespace std;
/*
	Camera class is for representing your camera in the worldspace. This class does all the computation for calculating exactly where a point in our 3D space would end up on the screen
*/
class Camera
{
private:
	Vector3d focusPoint;
	Matrix3d rot;
	Matrix<double,3,3> proj;


public:
	Vector3d Normal;
	Vector3d xAxis;
	Vector3d yAxis;
	Vector3d Location;
	dbl focalLength;


	void CalculateFocusPoint();
	Vector2d WorldToScreen(Vector3d Point);
	vector<Vector2d> WorldToScreenMat(Matrix<double, 3, -1> Points);
	vector<Vector2d> WorldToScreen(Triangle triangle); 

	void rotateAxis(dbl theta);
	void rotateNormalX(dbl theta);
	void rotateNormalY(dbl theta);
	Camera(Vector3d startLocation, dbl FocalLength);
};
