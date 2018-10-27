#include <cmath>
#include "Vector.h"
using namespace std;

VectorND getGradient(VectorND pos)
{
	return VectorND(pos.getDimensions());
}

float friction;
float gravity = 1.00f;
VectorND cPos;
VectorND cVel;

//ensure velocity never causes us to jump off the surface!

void Iterate()
{}