#include "WinHandle.h"
#include <stdio.h>

bool Win::WinOpen(int _WinWidth, int _WinHeight, const char *_WinTitle)
{
	
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	Window = glfwCreateWindow(_WinWidth, _WinHeight, _WinTitle, NULL, NULL);// x, y, char, mindow#, share
	if(!Window)
	{
		printf("Window Opening failed first time. Trying once more\n");
		Window = glfwCreateWindow(_WinWidth, _WinHeight, _WinTitle, NULL, NULL);
	}
	else
	{
		printf("Wondow creation was a success on first try\n");
	}
	
	glfwMakeContextCurrent (Window);

	/*glewExperimental = GL_TRUE;
	glewInit ();

	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"*/
	return true;
}
bool Win::WinCheckClose()
{
	if (glfwWindowShouldClose(Window))
	{
    
		return true;
	}
	// Keep running
	return false;
}
bool Win::Winupdate(bool _ClearScreen)
{
	if(WinCheckClose())
	{
		WinClose();//unload
		return false;
	}
	glfwGetFramebufferSize(Window, &WinWidth, &WinHeight);
	Ratio = WinWidth / WinHeight;

	glViewport(0, 0, WinWidth, WinHeight);
	if(_ClearScreen){glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}
	//glUseProgram(
	
	glfwSwapBuffers(Window);
	glfwPollEvents();
	
	return true;
}
bool Win::WinClose()
{
	glfwDestroyWindow(Window);
	glfwTerminate();
	return true;
}