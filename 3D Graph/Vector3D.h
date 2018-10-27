//AUTHOR: archit120

#pragma once
#include<cmath>
#define dbl long double

using namespace std;

class Vector3D
{
public:
	dbl X;
	dbl Y;
	dbl Z;
	Vector3D operator / (dbl a);
	Vector3D operator * (dbl a);
	Vector3D operator + (Vector3D a);
	Vector3D operator - (Vector3D a);

	dbl Magnitude();
	Vector3D Unit();
	dbl dotProduct(Vector3D a);
	Vector3D crossProduct(Vector3D a);
	Vector3D();
	Vector3D(dbl x, dbl y, dbl z);
};
