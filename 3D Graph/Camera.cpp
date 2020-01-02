//AUTHOR: archit120

#include"stdafx.h"
#include"Camera.h"
#include<vector>

using namespace Eigen;


const Vector3d negZ = Vector3d(0, 0, -1);

/*
	WorldToScreen for multiple points
*/
vector<Vector2d> Camera::WorldToScreenMat(Matrix<double, 3, -1> Points)
{
	Points.colwise() -= Location;

	Points = rot * Points;

	Matrix<double, 3, -1> screen_points = proj * Points;
	vector<Vector2d> ret_points;
	//Vector3d screen_point;
	for (int i = 0; i < screen_points.cols(); i++)
		if (screen_points(2, i) < 0)
			ret_points.push_back(Vector2d(screen_points(0, i) / Points(2, i), screen_points(1, i) / Points(2, i)));

	return ret_points;
}

/*
	Converts the 3D image into the projection according to the viewing angle of the camera so that it will be visible on the screen
*/
Vector2d Camera::WorldToScreen(Vector3d Point)
{
	Point = Point - Location;

	Point = rot * Point;

	Vector3d screen_point = proj * Point;
	//Vector3d screen_point;
	if (screen_point(2) < 0)
		return Vector2d(screen_point(0) / Point(2), screen_point(1) / Point(2));
	else
		return Vector2d(0, 0);
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
	Normal = (Normal* (cos(theta)) - Normal.cross(yAxis) * (sin(theta)));

	Vector3d v = Normal.cross(negZ);
	double s = v.norm();
	double c = Normal.dot(negZ);
	rot.setIdentity(3, 3);
	Matrix3d vx;
	vx << 0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0;
	rot = rot + vx + vx * vx / (1 + c);




	xAxis = Normal.cross(Vector3d(0, 1, 0)).normalized();
	yAxis = Normal.cross(xAxis);
//	Location = focusPoint - Normal * focalLength;
}
/*
	Function rotates the veiwing normal along the y axis by angle theta
*/
void Camera::rotateNormalY(dbl theta)
{
	Normal = (Normal* (cos(theta)) + Normal.cross(xAxis) * (sin(theta)));

	Vector3d v = Normal.cross(negZ);
	double s = v.norm();
	double c = Normal.dot(negZ);
	rot.setIdentity(3, 3);
	Matrix3d vx;
	vx << 0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0;
	rot = rot + vx + vx * vx / (1 + c);


	xAxis = Normal.cross(Vector3d(0, 1, 0)).normalized();
	yAxis = Normal.cross(xAxis);
	//Location = focusPoint - Normal * focalLength;

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
	xAxis = Normal.cross(Vector3d(0, 1, 0)).normalized();
	yAxis = Normal.cross(xAxis);



	Vector3d v = Normal.cross(negZ);
	double s = v.norm();
	double c = Normal.dot(negZ);
	rot.setIdentity(3, 3);
	Matrix3d vx;
	vx << 0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0;
	rot = rot + vx + vx * vx / (1 + c);

	proj.setZero();
	proj(0, 0) = focalLength;
	proj(1, 1) = focalLength;
	proj(2, 2) = 1;

}


vector<Vector2d> Camera::WorldToScreen(Triangle triangle)
{
	vector<Vector2d> v(3);
	v[0] = WorldToScreen(triangle.actual[0]);
	v[1] = WorldToScreen(triangle.actual[1]);
	v[2] = WorldToScreen(triangle.actual[2]);
	return v;
}
