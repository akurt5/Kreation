#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

namespace Window
{
	//The window created by Kreation
	static GLFWwindow *Window;
	//Dimensions of the GLFW Window
	static int WinHeight, WinWidth;

	//Opens a window.
	//
	//By default _WinWidth and _WinHeight are 0. They will be set to 75% of the Primary Monitors dimensions at run time.
	bool WinOpen(const char *_WinTitle = "Kreation Framework - v2.piss off - Test", int _WinWidth = 0, int _WinHeight = 0, bool _Resizable = false, int _Antialiasing = 4);
	//Checks to see if the window should close, and closes it if need be.
	bool WinCheckClose();
	//Updates perspective matrices and both width and height of the window.
	void WinSizeUpdate(GLFWwindow *_Window, int _WinWidth, int _WinHeight);
	//Updates the window by checking if it should close and clearing the screen.
	bool WinUpdate(bool _ClearScreen  = true);

	//Updates the window title to feature an FPS counter
	void UpdateFPS(GLFWwindow *_Window);

	//Log GL parameters and data and stuff.		It helps, alright.
	void LogGlParams();
}
#endif