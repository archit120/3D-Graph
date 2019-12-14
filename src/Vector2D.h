//AUTHOR: archit120

#pragma once
#include<cmath>
#define dbl long double

using namespace std;

class Vector2D
{
public:
	dbl X;
	dbl Y;
	Vector2D operator / (dbl a);
	Vector2D operator * (dbl a);
	Vector2D operator + (Vector2D a);
	Vector2D operator - (Vector2D a);

	dbl Magnitude();
	Vector2D Unit();
	dbl dotProduct(Vector2D a);
	Vector2D();
	Vector2D(dbl x, dbl y);
};
