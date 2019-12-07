
#include <Windows.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;
class Screen
{

private:
	int length;
	int height;
	HWND hWnd;
	HDC hdc;
	HDC hdcmem;
	HBITMAP buffer;
	HGDIOBJ gdiobject;
 inline double dist(double x1, double x2, double y1, double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
unsigned char* pBuffer;

public :

	void draw_polygon(vector<int> x, vector<int> y, unsigned char r, unsigned char g, unsigned char b); // Implement @Neha Dalmia

void put_pixel(int x, int y,  unsigned char r, unsigned char g, unsigned char b)
{
	if(x >0 && x < length && y >0 && y<height)
	{
		pBuffer[((y*length) + x )*3 ] = b;
		pBuffer[((y*length) + x )*3 + 1] = g;
		pBuffer[((y*length) + x)*3 + 2] = r;
	}
}

void put_pixel_2(int x, int y)
{
	if(x >0 && x < length && y >0 && y<height)
	{
		pBuffer[((y*length) + x )*3 ] = 255;
		pBuffer[((y*length) + x )*3 + 1] = 255;
		pBuffer[((y*length) + x)*3 + 2] = 255;
	}
}
void put_pixel_3(int x, int y)
{
	if (x >0 && x < length && y >0 && y<height)
	{

		pBuffer[((y*length) + x) * 3] = pBuffer[((y*length) + x) * 3] + 40  > 255 ? 255 : pBuffer[((y*length) + x) * 3] + 40;
		pBuffer[((y*length) + x) * 3 + 1] = pBuffer[((y*length) + x) * 3 ];
		pBuffer[((y*length) + x) * 3 + 2] = pBuffer[((y*length) + x) * 3 ];
	}
}
void draw_path(double x, double y, double ex, double ey, unsigned char r, unsigned char g , unsigned char b)
{
	for(double i = 0;i <= 1; i+=1.0f/dist(x,ex,y,ey))
	{
		put_pixel(x + (ex-x)*i, y+(ey-y)*i, r,g,b);
	}
}

void draw_path(vector<int> x, vector<int> y, unsigned char r, unsigned char g, unsigned char b)
{
	for(int i =0;i<x.size()-1;i++)
		draw_path(x[i],y[i],x[i+1],y[i+1], r, g, b);
}

void draw_circle_hollow(int x, int y, double R,  unsigned char rc, unsigned char g, unsigned char b)
{
	for(double r = R; r<=R;r+=1)
	{
		for(double r_x = 0; r_x<=r; r_x+=1)
		{
			double r_y = sqrt(r*r - r_x*r_x);
			put_pixel(x+r_x, y+r_y,  rc, g, b);
			put_pixel( x+r_x, y-r_y, rc, g, b);
			
			put_pixel(x-r_x, y+r_y, rc, g, b);
			put_pixel( x-r_x, y-r_y, rc, g, b);
		}
		put_pixel( x+r, y, rc, g, b);
		put_pixel( x-r, y, rc, g, b);
	}
}
void draw_circle_solid(int x, int y, double R,  unsigned char rc, unsigned char g, unsigned char b)
{
	for(double r = 0; r<=R;r+=0.4)
	{
		for(double theta = 0; theta <= 2*3.14; theta+=3.14/2/r)
		{
			put_pixel(x+cos(theta)*r, y+ sin(theta)*r,  rc, g, b);
			
		}
		put_pixel( x+r, y, rc, g, b);
		put_pixel( x-r, y, rc, g, b);
	}
}

void clear()
{
	memset(pBuffer, 0, length*height*3);
}

void Draw()
{
	BitBlt(hdc, 0, 0, length,height,hdcmem, 0, 0, SRCCOPY);

}

Screen(int x, int y)
{
	BITMAPINFO bmi;
	bmi.bmiHeader.biBitCount=24;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biCompression = BI_RGB;
	
	bmi.bmiHeader.biHeight = y;
	bmi.bmiHeader.biWidth = x;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight*bmi.bmiHeader.biBitCount/8;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	
	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	hdcmem = CreateCompatibleDC(hdc);
	gdiobject = SelectObject(hdcmem, buffer);
	buffer = CreateDIBSection(hdcmem,& bmi, DIB_RGB_COLORS,(void**)&pBuffer,NULL,0);
	SelectObject(hdcmem, buffer);
	length = x;
	height = y;
}

~Screen()
{
	ReleaseDC(hWnd, hdc);
	DeleteDC(hdcmem);
	DeleteObject(buffer);
}

};
