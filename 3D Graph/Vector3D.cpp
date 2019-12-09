//AUTHOR: archit120

#include"stdafx.h"
#include"Vector3D.h"
#include<cmath>
#define dbl long double
/*
	3D Vector Operators
*/
Vector3D Vector3D::operator / (dbl a)
{
	return Vector3D(X / a, Y / a, Z / a);
}
Vector3D Vector3D::operator * (dbl a)
{
	return Vector3D(X * a, Y * a, Z * a);
}
Vector3D Vector3D::operator + (Vector3D a)
{
	return Vector3D(X + a.X, Y + a.Y, Z + a.Z);
}
Vector3D Vector3D::operator - (Vector3D a)
{
	return Vector3D(X - a.X, Y - a.Y, Z - a.Z);
}
/*
	Function to calculate the length of the vector
*/
dbl Vector3D::Magnitude()
{
	return sqrt(X*X + Y * Y + Z * Z);
}
/*
	Returns the unit Vector of the given vector
*/
Vector3D Vector3D::Unit()
{
	return Vector3D(X, Y, Z) / Magnitude();
}
/*
	function computes the Dot product
*/
dbl Vector3D::dotProduct(Vector3D a)
{
	return X * a.X + Y * a.Y + Z * a.Z;
}
/*
	function computes the Cross product
*/
Vector3D Vector3D::crossProduct(Vector3D a)
{
	return Vector3D(Y*a.Z - Z * a.Y, Z*a.X - X * a.Z, X*a.Y - Y * a.X);
}
Vector3D::Vector3D()
{
	X = Y = Z = 0;
}
/*
	Creates the 3D Vector
*/
Vector3D::Vector3D(dbl x, dbl y, dbl z)
{
	X = x, Y = y, Z = z;
}
