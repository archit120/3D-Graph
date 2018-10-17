#include<cmath>
#define dbl long double

class Vector3D
{
public:
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
		return sqrt(X*X + Y * Y + Z * Z);
	}
	Vector3D Unit()
	{
		return Vector3D(X, Y, Z) / Magnitude();
	}
	dbl dotProduct(Vector3D a)
	{
		return X * a.X + Y * a.Y + Z * a.Z;
	}
	Vector3D crossProduct(Vector3D a)
	{
		return Vector3D(Y*a.Z - Z * a.Y, Z*a.X - X * a.Z, X*a.Y - Y * a.X);
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

class Triangle
{
public:
	Vector3D actual[3];
	Vector3D projected[3];
	Vector3D normal;

	dbl CalculateNormal()
	{
		normal = (actual[1] - actual[0]).crossProduct(actual[2] - actual[0]);
		normal = normal.Unit();
		return normal.dotProduct(Vector3D(0, 0, 1));
	}

};

void VertexToTriangle(Vector3D** vertex, int sizex, int sizey, Triangle* faces)
{
	//Triangle* faces = new Triangle[2*(sizex - 1)*(sizey - 1)];
	int count = 0;
	for (int y = 1; y < sizey-1; y++)
	{
		for (int x = 0; x < sizex-1; x++)
		{
			faces[count].actual[0] = vertex[x][y];
			faces[count].actual[1] = vertex[x + 1][y];
			faces[count].actual[2] = vertex[x + 1][y + 1];
			faces[count].projected[0] = Vector3D((x - 500) / 10.0, (y - 500) / 10.0, 0);
			faces[count].projected[1] = Vector3D((x + 1 - 500) / 10.0, (y - 500) / 10.0, 0);
			faces[count].projected[2] = Vector3D((x + 1 - 500) / 10.0, (y + 1 - 500) / 10.0, 0);
			if (faces[count].CalculateNormal() < 0)
			{
				faces[count].normal = faces[count].normal * (-1);
			}
			count++;
			faces[count].actual[0] = vertex[x][y];
			faces[count].actual[1] = vertex[x + 1][y];
			faces[count].actual[2] = vertex[x][y - 1];
			faces[count].projected[0] = Vector3D((x - 500) / 10.0, (y - 500) / 10.0, 0);
			faces[count].projected[1] = Vector3D((x + 1 - 500) / 10.0, (y - 500) / 10.0, 0);
			faces[count].projected[2] = Vector3D((x - 500) / 10.0, (y - 1 - 500) / 10.0, 0);
			if (faces[count].CalculateNormal() < 0)
			{
				faces[count].normal = faces[count].normal * (-1);
			}
			count++;
		}
	}
	for (int x = 0; x < sizex - 1; x++)
	{
		faces[count].actual[0] = vertex[x][0];
		faces[count].actual[1] = vertex[x + 1][0];
		faces[count].actual[2] = vertex[x + 1][1];
		faces[count].projected[0] = Vector3D((x - 500) / 10.0, (0 - 500) / 10.0, 0);
		faces[count].projected[1] = Vector3D((x + 1 - 500) / 10.0, (0 - 500) / 10.0, 0);
		faces[count].projected[2] = Vector3D((x + 1 - 500) / 10.0, (1 - 500) / 10.0, 0);
		if (faces[count].CalculateNormal() < 0)
		{
			faces[count].normal = faces[count].normal * (-1);
		}
		count++;
		faces[count].actual[0] = vertex[x][sizey - 1];
		faces[count].actual[1] = vertex[x + 1][sizey - 1];
		faces[count].actual[2] = vertex[x][sizey - 2];
		faces[count].projected[0] = Vector3D((x - 500) / 10.0, (sizey - 1 - 500) / 10.0, 0);
		faces[count].projected[1] = Vector3D((x + 1 - 500) / 10.0, (sizey - 1 - 500) / 10.0, 0);
		faces[count].projected[2] = Vector3D((x - 500) / 10.0, (sizey - 2 - 500) / 10.0, 0);
		if (faces[count].CalculateNormal() < 0)
		{
			faces[count].normal = faces[count].normal * (-1);
		}
		count++;
	}
}

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
		focusPoint = Location + Normal * focalLength;
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

	void rotateAxis(dbl theta)
	{
		yAxis = (yAxis* (cos(theta)) + yAxis.crossProduct(Normal) * (sin(theta)));
		xAxis = (xAxis* (cos(theta)) + xAxis.crossProduct(Normal) * (sin(theta)));
	}
	void rotateNormalX(dbl theta)
	{
		Normal = (Normal* (cos(theta)) + Normal.crossProduct(yAxis) * (sin(theta)));
		xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
		yAxis = Normal.crossProduct(xAxis);
		Location = focusPoint - Normal * focalLength;
	}
	void rotateNormalY(dbl theta)
	{
		Normal = (Normal* (cos(theta)) + Normal.crossProduct(xAxis) * (sin(theta)));
		xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
		yAxis = Normal.crossProduct(xAxis);
		Location = focusPoint - Normal * focalLength;

	}
	Camera(Vector3D startLocation, dbl FocalLength)
	{
		Location = startLocation;
		Normal = (Vector3D(0, 0, 0) - startLocation).Unit();
		focalLength = FocalLength;
		//Create a random y Axis
		xAxis = Normal.crossProduct(Vector3D(0, 0, -1)).Unit();
		yAxis = Normal.crossProduct(xAxis);
	}
};


