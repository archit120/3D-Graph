#include <Windows.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;


#define dbl long double

class VectorND
{

	int Dimensions;

public:
	double* Values;
	int getDimensions()
	{
		return Dimensions;
	}
	VectorND operator / (dbl a)
	{
		double* values = new double[Dimensions]();
		for (int i = 0; i < Dimensions; i++)
		{
			values[i] = Values[i] / a;
		}
		VectorND r = VectorND(Dimensions, values);
		delete values;
		return r;
	}
	VectorND operator * (dbl a)
	{
		double* values = new double[Dimensions]();
		for (int i = 0; i < Dimensions; i++)
		{
			values[i] = Values[i] * a;
		}
		VectorND r = VectorND(Dimensions, values);
		delete values;
		return r;
	}
	VectorND operator + (VectorND a)
	{
		if (a.Dimensions != Dimensions)
			throw new exception("Dimension mismatch");
		double* values = new double[Dimensions]();
		for (int i = 0; i < Dimensions; i++)
		{
			values[i] = Values[i] + a.Values[i];
		}
		VectorND r = VectorND(Dimensions, values);
		delete values;
		return r;
	}
	VectorND operator - (VectorND a)
	{
		if (a.Dimensions != Dimensions)
			throw new exception("Dimension mismatch");
		double* values = new double[Dimensions]();
		for (int i = 0; i < Dimensions; i++)
		{
			values[i] = Values[i] - a.Values[i];
		}
		VectorND r = VectorND(Dimensions, values);
		delete values;
		return r;
	}

	dbl Magnitude()
	{
		double value = 0;
		for (int i = 0; i < Dimensions; i++)
		{
			value += Values[i] * Values[i];
		}
		return sqrt(value);
	}
	VectorND Unit()
	{
		return VectorND(Dimensions, Values) / Magnitude();
	}
	dbl dotProduct(VectorND a)
	{
		if (a.Dimensions != Dimensions)
			throw new exception("Dimension mismatch");

		double value = 0;
		for (int i = 0; i < Dimensions; i++)
		{
			value += Values[i] * a.Values[i];
		}

		return value;
	}
	VectorND crossProduct(VectorND a)
	{
		return VectorND(Y*a.Z - Z * a.Y, Z*a.X - X * a.Z, X*a.Y - Y * a.X);
	}
	VectorND(int n)
	{
		Dimensions = n;
		Values = new double[n]();
	}
	VectorND(dbl x, dbl y, dbl z) : VectorND(3)
	{
		Values[0] = x, Values[1] = y, Values[2] = z;
	}
	VectorND(int n, double* _values) : VectorND(n)
	{
		for (int i = 0; i < n; i++)
			Values[i] = _values[i];
	}
};
