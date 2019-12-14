//AUTHOR: archit120

#include"stdafx.h"
#include"Vector2D.h"
#include<cmath>

#define dbl long double
Vector2D Vector2D::operator / (dbl a)
{
	return Vector2D(X / a, Y / a);
}
Vector2D Vector2D::operator * (dbl a)
{
	return Vector2D(X * a, Y * a);
}
Vector2D Vector2D::operator + (Vector2D a)
{
	return Vector2D(X + a.X, Y + a.Y);
}
Vector2D Vector2D::operator - (Vector2D a)
{
	return Vector2D(X - a.X, Y - a.Y);
}

dbl Vector2D::Magnitude()
{
	return sqrt(X*X + Y * Y);
}
Vector2D Vector2D::Unit()
{
	return Vector2D(X, Y) / Magnitude();
}
dbl Vector2D::dotProduct(Vector2D a)
{
	return X * a.X + Y * a.Y;
}
Vector2D::Vector2D()
{
	X = Y = 0;
}
Vector2D::Vector2D(dbl x, dbl y)
{
	X = x, Y = y;
}