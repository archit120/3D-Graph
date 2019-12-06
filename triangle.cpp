

#include "pch.h"
#include <iostream>

using namespace std;
double max(double a, double b, double c)
{
	if (a >= b && a >= c)
		return a;
	else if (b >= a && b >= c)
		return b;
	else
		return c;
}

double min(double a, double b, double c)
{
	if (a <= b && a <= c)
		return a;
	else if (b <= c && b <= a)
		return b;
	else
		return c;
}

int main()
{
	double x1 = 2.0f, x2 = 4.0f, x3 = 6.0f; //arbitrary coordinates
	double y1 = 2.0f, y2 = 5.0f, y3 = 3.0f;
	double xmax = max(x1, x2, x3);
	double xmin = min(x1, x2, x3);
	double ymax = max(y1, y2, y3);
	double ymin = min(y1, y2, y3);
	for (double i = ymax; i >= ymin; i -= 0.05f)
	{
		for (double j = xmin; j <= xmax; j += 0.05f)
		{
			double dot1 = (y2 - y1)*(j - x1) + (x1 - x2)*(i - y1);
			double dot2 = (y3 - y2)*(j - x2) + (x2 - x3)*(i - y2);
			double dot3 = (y1 - y3)*(j - x3) + (x3 - x1)*(i - y3);
			if (dot1 >= 0.0f&&dot2 >= 0.0f&&dot3 >= 0.0f)
				cout << "*";
			else
				cout << " ";

		}
		cout << "\n";
	}
}


