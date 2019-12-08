#pragma once
#include "render.h"
#include "Camera.h"
#include <conio.h>

class ControlLoop
{
public:
	static void loop(Camera& ca, double& t);
	static void UserInput(Camera& ca);
};