// 3D Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "render.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <conio.h>

#define dbl long double

using namespace std;


class Vector3D
{
public :
	dbl X;
	dbl Y;
	dbl Z;
	Vector3D operator / (dbl a)
	{
		return Vector3D(X / a, Y / a, Z / a);
	}
	Vector3D operator * (dbl a)
	{
		return Vector3D(X * a, Y * a, Z * a);
	}
	Vector3D operator + (Vector3D a)
	{
		return Vector3D(X + a.X, Y + a.Y, Z + a.Z);
	}
	Vector3D operator - (Vector3D a)
	{
		return Vector3D(X - a.X, Y - a.Y, Z - a.Z);
	}

	dbl Magnitude()
	{
		return sqrt(X*X + Y*Y + Z*Z);
	}
	Vector3D Unit()
	{
		return Vector3D(X, Y, Z) / Magnitude();
	}
	dbl dotProduct(Vector3D a)
	{
		return X*a.X + Y*a.Y + Z*a.Z;
	}
	Vector3D crossProduct(Vector3D a)
	{
		return Vector3D(Y*a.Z - Z*a.Y, Z*a.X - X*a.Z, X*a.Y - Y*a.X);
	}
	Vector3D()
	{
		X = Y = Z = 0;
	}
	Vector3D(dbl x, dbl y, dbl z)
	{
		X = x, Y = y, Z = z;
	}
};

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


	void CalculateFocusPoint()
	{
		focusPoint = Location + Normal* focalLength;
	}
	Vector3D WorldToScreen(Vector3D Point)
	{
		CalculateFocusPoint();
		Vector3D dir = Point - focusPoint;
		Vector3D rel = Point - Location;
	 if ((focusPoint - Location).dotProduct(Normal) * rel.dotProduct(Normal) < 0)
		{
			return Vector3D(-10000, -10000, -10000);
		}
	 if (!dir.dotProduct(Normal) )
		{
		return Vector3D(-10000, -10000, -10000);
		} 
	 if ( focalLength > abs(rel.dotProduct(Normal)))
		{
		return Vector3D(-10000, -10000, -10000);
		}

		dbl ln = Location.dotProduct(Normal);
		dbl lambda = (ln - Point.dotProduct(Normal)) / dir.dotProduct(Normal);
		Vector3D POI = Point + dir*lambda;
		rel = POI - Location;
		//invert for virtual image
		double x = -xAxis.dotProduct(rel);
		double y = -yAxis.dotProduct(rel);
		return Vector3D(x, y, 0);
	}

	void rotateAxis(dbl theta)
	{
		yAxis = (yAxis* (cos(theta)) + yAxis.crossProduct(Normal) * (sin(theta) )) ;
		xAxis =(xAxis* (cos(theta) ) + xAxis.crossProduct(Normal) * (sin(theta) ));
	}
	void rotateNormalX(dbl theta)
	{
		Normal = (Normal* (cos(theta) ) + Normal.crossProduct(yAxis) * (sin(theta) )) ;
		xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
		yAxis = Normal.crossProduct(xAxis);
		Location = focusPoint - Normal *focalLength;
	}
	void rotateNormalY(dbl theta)
	{
		Normal = (Normal* (cos(theta)) + Normal.crossProduct(xAxis) * (sin(theta) ))  ;
		xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
		yAxis = Normal.crossProduct(xAxis);
		Location = focusPoint - Normal *focalLength;

	}
	Camera(Vector3D startLocation, dbl FocalLength)
	{
		Location = startLocation;
		Normal = (Vector3D(0,0,0)-startLocation).Unit();
		focalLength = FocalLength;
		//Create a random y Axis
		xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
		yAxis = Normal.crossProduct(xAxis);
	}
};

dbl function(dbl y, dbl x, dbl t)
{
	//if(y < 50 && x < 50)
	return sin(sqrt((x +25)*(x +25) + (y - 10)*(y - 10)) + t)  + sin(sqrt((x+25)*(x+25) + (y +10)*(y +10)) + 2*t);
	//return sqrt(y*x);
	//return 0;
}

int main()
{
	Camera ca(Vector3D(10, 10, 10), 290);
	ca.Location = Vector3D(305, 0, 4);
	//ca.Normal = Vector3D(-1, 0, 0);
	ca.yAxis = Vector3D(0, 0, 1);
	ca.xAxis = Vector3D(0, 1, 0);
	ca.Normal = ca.yAxis.crossProduct(ca.xAxis);
	Screen s(2000, 2000);
	_getch();
	SetCursorPos(500, 500);
	double t = 0;
	while (true)
	{
		t += 0.1;
		s.clear();
		if (_kbhit())
		{
			char c;
			c = _getch();

			switch (c)
			{
			case 'w':
				ca.Location = ca.Location + ca.Normal;
				break;
			case 's':
				ca.Location = ca.Location - ca.Normal;
				break;
			case 'a':
				ca.Location = ca.Location - ca.xAxis;
				break;
			case 'd':
				ca.Location = ca.Location + ca.xAxis;
				break;

			case 't':
				ca.Location = ca.Location + ca.yAxis;
				break;
			case 'g':
				ca.Location = ca.Location - ca.yAxis;
				break;
			case 'q':
				ca.rotateAxis(0.1);
				break;
			case 'e':
				ca.rotateAxis(-0.1);
				break;
			case 'y':
				ca.rotateNormalX(0.01);
				break;
			case 'h':
				ca.rotateNormalX(-0.01);
				break;
			case 'u':
				ca.rotateNormalY(0.01);
				break;
			case 'j':
				ca.rotateNormalY(-0.01);
				break;
			}
		}

	POINT p;
		GetCursorPos(&p);

		if (p.x != 500)
		{
			ca.rotateNormalX(-0.001 * (p.x - 500));
			p.x = 500;
		}
		if (p.y != 500)
		{
			ca.rotateNormalY(-0.001 * (p.y - 500));
			p.y = 500;
		}

		SetCursorPos(p.x, p.y);
		for (double x = -50; x < 50; x+=0.1)
		{
			for (double y = -50; y < 50; y+=0.1)
			{
				dbl z = function(y, x,-t);
				//cout << z << "\n";
				auto o = ca.WorldToScreen(Vector3D(x, y, z));
				//cout << o.X << " " << o.Y << " " << o.Z<< "\n";
				s.put_pixel_3(o.X+ 500, o.Y + 500);
			}
		}
		s.Draw();
		//..cout << "render" << "\n";
		//cout << ca.Location.X << " " << ca.Location.Y << " " << ca.Location.Z << "\n";
		//cout << ca.Normal.X << " " << ca.Normal.Y << " " << ca.Normal.Z << "\n";
 		//_getch();
		//s.clear();
	}
	_getch();
    return 0;
}

