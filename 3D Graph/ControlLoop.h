#pragma once
#include "render.h"
#include "Camera.h"
#include <conio.h>

class ControlLoop
{
public:
	static bool loop(Camera& ca, double& t);
	static bool UserInput(Camera& ca);
};