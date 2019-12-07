//AUTHOR: archit120

#pragma once
#include "Vector2D.h"
#include"Vector3D.h"
#include <vector>
#include"Triangle.h"
#define dbl long double

using namespace std;

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
	Vector2D WorldToScreen(Vector3D Point);

	vector<Vector2D> WorldToScreen(Triangle triangle); //Implement @Neha Dalmia

	void rotateAxis(dbl theta);
	void rotateNormalX(dbl theta);
	void rotateNormalY(dbl theta);
	Camera(Vector3D startLocation, dbl FocalLength);
};
