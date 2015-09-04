#include "WindowHandle.h"
#include "LogHandle.h"
#include "InputHandle.h"
#include "ShaderHandle.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


bool Window::WinOpen( const char *_WinTitle, int _WinWidth, int _WinHeight, bool _Resizable, int _Antialiasing)
{
	srand(time(nullptr));

	assert(CreateLog());
	Log("Starting GLFW\n\n%s\n\n", glfwGetVersionString());// i guess it'll tell us what glfw version we're using
	glfwSetErrorCallback(GlfwErrorCallback);//hooks my guy up with their guy..!
	if (!glfwInit())
	{
		LogError("Failed to init glfw, trying once more...(As if that will help)\n\n");
		if (!glfwInit())
		{
			LogError("Glfw failed on second try, to no ones surprise... Exiting.\n\n");
			return false;
		}
	}
	else
	{
		Log("Glfw init was a success on first attempt!. (shot)\n\n");
	}

	
	
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);// this is the .3
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	*/

	//Apple OS Only Stuff  ^^^^
	glfwWindowHint(GLFW_SAMPLES, _Antialiasing); // 4x antialiasing by default
	glfwWindowHint(GLFW_RESIZABLE, _Resizable); //if false window is not resizable

	if((!_WinWidth) && (!_WinHeight))// If dimensions were unspecified 
	{
		GLFWmonitor *Monitor = glfwGetPrimaryMonitor();// derrrr.. Gets primary monitor;
		const GLFWvidmode *Mode = glfwGetVideoMode(Monitor);//This probably get the resolution(video mode) of the monitor.
		WinWidth = Mode->width;//I'll take that!
		WinHeight = Mode->height;//  .. And that!
		Window = glfwCreateWindow(WinWidth * 0.75, WinHeight * 0.75, _WinTitle, NULL, NULL);// Making a fullscreen window is like asking for HIV and getting Downs syndrome. So we go with 75%.
	}
	else
	{
		Window = glfwCreateWindow(_WinWidth, _WinHeight, _WinTitle, NULL, NULL);// x, y, char, mindow#, share
	}

	if(!Window)
	{
		LogError("Window Opening failed first time. Trying once more\n\n");
		Window = glfwCreateWindow(_WinWidth, _WinHeight, _WinTitle, NULL, NULL);
	}
	else
	{
		Log("Wondow creation was a success on first try!. (shot)\n\n");
	}
	
	glfwMakeContextCurrent (Window);

	glfwSetWindowSizeCallback(Window, WinSizeUpdate);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)//Initialising GLEW you idiot.
	{
		LogError("Failed to init glew, trying once more...(As if that will help)\n\n");
		if (glewInit() != GLEW_OK)
		{
			LogError("Glew failed on second try, to no ones surprise... Exiting.\n\n");
			return false;
		}
	}
	else
	{
		if(rand() % 3 == 0)
		{
			Log("Glew init was a FAILURE!\n");
			Log("Just kidding it was really a success on the first attempt!. (shot)\n\n");
		}
		else
		{
			Log("Glew init was a success on the first attempt!. (shot)\n\n");
		}
	}

	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);

	/**/
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	Log ("Renderer: %s\n", renderer);
	Log ("OpenGL version supported %s\n\n", version);
	
	LogGlParams();
	
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	return true;
}
bool Window::WinCheckClose()
{
	if(KEY_PRESS == KeyStatus(Window, KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(Window, 1);
	}

	if (glfwWindowShouldClose(Window))
	{
		glfwDestroyWindow(Window);
		glfwTerminate();
		
		SignLog();
		return false;
	}
	// Keep running
	return true;
}
void Window::WinSizeUpdate(GLFWwindow *_Window, int _WinWidth, int _WinHeight)
{
		WinWidth = _WinWidth;
		WinHeight = _WinHeight;
		
		//Matrix stuff here plx
}
bool Window::WinUpdate(bool _ClearScreen)
{
	UpdateFPS(Window);

	glfwSwapBuffers(Window);
	if(_ClearScreen){glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}
	glViewport(0, 0, WinWidth, WinHeight);
	glfwGetFramebufferSize(Window, &WinWidth, &WinHeight);
	
	glfwPollEvents();
	
	return WinCheckClose();
}
void Window::UpdateFPS(GLFWwindow *_Window)
{
	static double PrevSecs = glfwGetTime();//static because we want it to remain in memory after function is done, dawg.
	static int FrameCount;//static shit also can't be reinitialised either.
	double CurrSecs = glfwGetTime();
	double ElapSecs = CurrSecs - PrevSecs;
	if(ElapSecs > 0.25)
	{
		PrevSecs = CurrSecs;
		double FPS = (double)FrameCount / ElapSecs;
		char tmp[128];
		
		sprintf_s(tmp, "Kreation Framework - v2.piss off - Test FPS: %.2f", FPS);
		glfwSetWindowTitle(_Window, tmp);
		FrameCount = 0;
	}
	FrameCount++;
}
void Window::LogGlParams()// In this functionwe print the names and values for some opengl parameters.
{
	GLenum Params[] = //values
	{
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* ParamNames[] = //names
	{
		"\nGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS	",
		"\nGL_MAX_CUBE_MAP_TEXTURE_SIZE		",
		"\nGL_MAX_DRAW_BUFFERS			",
		"\nGL_MAX_FRAGMENT_UNIFORM_COMPONENTS	",
		"\nGL_MAX_TEXTURE_IMAGE_UNITS		",
		"\nGL_MAX_TEXTURE_SIZE			",
		"\nGL_MAX_VARYING_FLOATS			",
		"\nGL_MAX_VERTEX_ATTRIBS			",
		"\nGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS	",
		"\nGL_MAX_VERTEX_UNIFORM_COMPONENTS	",
		"\nGL_MAX_VIEWPORT_DIMS			",
		"\nGL_STEREO				",
  };
	Log("GL Context Params:\n");
	char msg[256];// do i even need this??????
	//integers - only works if the order is 0-10 integer return types. //I copied this comment from AntonGerdlan.net/opengl/glcontext2.html because i do not understand this code yet.
	//I guess the Params are represented as integers e.g. GL_MAX_DRAW_BUFFERS = 8. <---100% made up.! <-- actually plausable though. 
	for(int i=0;i<10;i++)
	{
		int v = 0;
		glGetIntegerv(Params[i], &v);
		Log("%s %i\n", ParamNames[i], v);
	}
	//others. Other than integers i guess??
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv(Params[10], v);
	Log("%s %i %i\n", ParamNames[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv (Params[11], &s);
	Log("%s %u\n\n", ParamNames[11], (unsigned int)s);

}
