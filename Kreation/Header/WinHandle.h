#ifndef WIN_H
#define WIN_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ShaderHandle.h"

class Win
{
public:

	//The window created by Kreation
	GLFWwindow *Window;
	//Dimension of the GLFW Window
	int WinHeight, WinWidth;
	float Ratio;

	//Opens a window.
	bool WinOpen(int _WinWidth, int _WinHeight, const char *_WinTitle);
	//Checks to see if the window should close
	bool WinCheckClose();
	//Updates the window by checking if it should close and clearing the screen.
	bool Winupdate(bool _ClearScreen);
	//Destroys the window
	bool WinClose();
	
};
#endif