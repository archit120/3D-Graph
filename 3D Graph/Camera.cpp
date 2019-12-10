//AUTHOR: archit120

#include"stdafx.h"
#include"Camera.h"
#include<vector>

using namespace Eigen;

/*
	Calculates the focus point of the camera 
*/
void Camera::CalculateFocusPoint()
{
	focusPoint = Location + Normal * focalLength;
}

/*
	Converts the 3D image into the projection according to the viewing angle of the camera so that it will be visible on the screen
*/
Vector2d Camera::WorldToScreen(Vector3d Point)
{
	CalculateFocusPoint();
	Vector3d dir = Point - focusPoint;
	Vector3d rel = Point - Location;
	if ((focusPoint - Location).dot(Normal) * rel.dot(Normal) < 0)
	{
		return Vector2d(-10000, -10000);
	}
	if (!dir.dot(Normal))
	{
		return Vector2d(-10000, -10000);
	}
	if (focalLength > abs(rel.dot(Normal)))
	{
		return Vector2d(-10000, -10000);
	}


	dbl ln = Location.dot(Normal);
	dbl lambda = (ln - Point.dot(Normal)) / dir.dot(Normal);
	Vector3d POI = Point + dir * lambda;
	rel = POI - Location;
	//invert for virtual image
	double x = -xAxis.dot(rel);
	double y = -yAxis.dot(rel);
	return Vector2d(x, y);
}
/*
	Function rotates the Axes by a given angle theta
*/
void Camera::rotateAxis(dbl theta)
{
	yAxis = (yAxis* (cos(theta)) + yAxis.cross(Normal) * (sin(theta)));
	xAxis = (xAxis* (cos(theta)) + xAxis.cross(Normal) * (sin(theta)));
}
/*
	Function rotates the veiwing normal along the x axis by angle theta
*/
void Camera::rotateNormalX(dbl theta)
{
	Normal = (Normal* (cos(theta)) + Normal.cross(yAxis) * (sin(theta)));
	xAxis = Normal.cross(Vector3d(0, 0, -1)).normalized();
	yAxis = Normal.cross(xAxis);
	Location = focusPoint - Normal * focalLength;
}
/*
	Function rotates the veiwing normal along the y axis by angle theta
*/
void Camera::rotateNormalY(dbl theta)
{
	Normal = (Normal* (cos(theta)) + Normal.cross(xAxis) * (sin(theta)));
	xAxis = Normal.cross(Vector3d(0, 0, -1)).normalized();
	yAxis = Normal.cross(xAxis);
	Location = focusPoint - Normal * focalLength;

}
/*
	Initialtes the viewing angle of the camera or the Image that will appear on the screen
*/
Camera::Camera(Vector3d startLocation, dbl FocalLength)
{
	Location = startLocation;
	Normal = (Vector3d(0, 0, 0) - startLocation).normalized();
	focalLength = FocalLength;
	//Create a random y Axis
	xAxis = Normal.cross(Vector3d(0, 0, -1)).normalized();
	yAxis = Normal.cross(xAxis);
}


vector<Vector2d> Camera::WorldToScreen(Triangle triangle)
{
	vector<Vector2d> v(3);
	v[0] = WorldToScreen(triangle.actual[0]);
	v[1] = WorldToScreen(triangle.actual[1]);
	v[2] = WorldToScreen(triangle.actual[2]);
	return v;
}
