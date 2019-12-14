#pragma once
#ifdef _WIN32
#include "render.h"
#include <conio.h>
#elif __APPLE__||__linux__
#include "renderlinux.h"
#endif
#include <iostream>
#include "Camera.h"
class ControlLoop
{
public:
	static void loop(Camera& ca, double& t);
	static void UserInput(Camera& ca);
};