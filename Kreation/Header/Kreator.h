#ifndef KREATOR_H
#define KREATOR_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "InputHandle.h"
#include "WinHandle.h"
#include "TextureHandle.h"


namespace //Kreator//							Create and handle windows and background shit -GLFW. Maybe Kreator should be a wrapper for windows and key handling and such...
//class Kreator
{


	Win WindowHandle;
	Input InputHandle;
	Texture TextureHandle;
	
}//;

#endif