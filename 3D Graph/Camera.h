//AUTHOR: archit120

#pragma once
#include"Vector3D.h"
#define dbl long double

using namespace std;
/*
	Camera class is for representing your camera in the worldspace. This class does all the computation for calculating exactly where a point in our 3D space would end up on the screen
*/
class Camera
{
private:
	Vector3D focusPoint;

public:
	Vector3D Normal;
	Vector3D xAxis;
	Vector3D yAxis;
	Vector3D Location;
	dbl focalLength;


	void CalculateFocusPoint();
	Vector3D WorldToScreen(Vector3D Point);
	void rotateAxis(dbl theta);
	void rotateNormalX(dbl theta);
	void rotateNormalY(dbl theta);
	Camera(Vector3D startLocation, dbl FocalLength);
};
