//AUTHOR: archit120

#include"stdafx.h"
#include"Camera.h"
#include"Vector3D.h"

void Camera::CalculateFocusPoint()
{
	focusPoint = Location + Normal * focalLength;
}

Vector3D Camera::WorldToScreen(Vector3D Point)
{
	CalculateFocusPoint();
	Vector3D dir = Point - focusPoint;
	Vector3D rel = Point - Location;
	if ((focusPoint - Location).dotProduct(Normal) * rel.dotProduct(Normal) < 0)
	{
		return Vector3D(-10000, -10000, -10000);
	}
	if (!dir.dotProduct(Normal))
	{
		return Vector3D(-10000, -10000, -10000);
	}
	if (focalLength > abs(rel.dotProduct(Normal)))
	{
		return Vector3D(-10000, -10000, -10000);
	}

	dbl ln = Location.dotProduct(Normal);
	dbl lambda = (ln - Point.dotProduct(Normal)) / dir.dotProduct(Normal);
	Vector3D POI = Point + dir * lambda;
	rel = POI - Location;
	//invert for virtual image
	double x = -xAxis.dotProduct(rel);
	double y = -yAxis.dotProduct(rel);
	return Vector3D(x, y, 0);
}

void Camera::rotateAxis(dbl theta)
{
	yAxis = (yAxis* (cos(theta)) + yAxis.crossProduct(Normal) * (sin(theta)));
	xAxis = (xAxis* (cos(theta)) + xAxis.crossProduct(Normal) * (sin(theta)));
}

void Camera::rotateNormalX(dbl theta)
{
	Normal = (Normal* (cos(theta)) + Normal.crossProduct(yAxis) * (sin(theta)));
	xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
	yAxis = Normal.crossProduct(xAxis);
	Location = focusPoint - Normal * focalLength;
}

void Camera::rotateNormalY(dbl theta)
{
	Normal = (Normal* (cos(theta)) + Normal.crossProduct(xAxis) * (sin(theta)));
	xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
	yAxis = Normal.crossProduct(xAxis);
	Location = focusPoint - Normal * focalLength;

}

Camera::Camera(Vector3D startLocation, dbl FocalLength)
{
	Location = startLocation;
	Normal = (Vector3D(0, 0, 0) - startLocation).Unit();
	focalLength = FocalLength;
	//Create a random y Axis
	xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
	yAxis = Normal.crossProduct(xAxis);
}