//AUTHOR: ShreyanshDarshan

#include"stdafx.h"
#include"Triangle.h"
#include"Vector3D.h"
#define dbl long double
/*
	Checks whether the normal between base and hypotenuse is coming out of the plane(returns positive value) or into the plane (returns negative value)
*/
dbl Triangle::CalculateNormal()
{
	return -1;
}
//void Triangle::VertexToTriangle(Vector3D** vertex, int x, int y, int type)
//{
//	//Triangle* faces = new Triangle[2*(sizex - 1)*(sizey - 1)]; 
//	actual[0] = vertex[x][y];
//	actual[1] = vertex[x + 1][y];
//	actual[2] = vertex[x + 1][y + 1];
//	projected[0] = Vector3D((x - 500) / 10.0, (y - 500) / 10.0, 0);
//	projected[1] = Vector3D((x + 1 - 500) / 10.0, (y - 500) / 10.0, 0);
//	projected[2] = Vector3D((x + type - 500) / 10.0, (y + type * 2 - 1 - 500) / 10.0, 0);
//	if (CalculateNormal() < 0)
//	{
//		normal = normal * (-1);
//	}
//}