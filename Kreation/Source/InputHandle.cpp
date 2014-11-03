#include "InputHandle.h"

#include "GLFW\glfw3.h"

bool Input::KeyDown(GLFWwindow *_Window, int _Key)
{
	return glfwGetKey(_Window, _Key);
}
bool Input::KeyOnRelease(GLFWwindow *_Window, int _Key)
{
	static bool Prev;
	bool Curr = false;
	Curr = KeyDown(_Window, _Key);
	if ((Prev) && (!Curr))
	{
		Prev = Curr;
		return true;
	}
	Prev = Curr;
	return false;
}
bool Input::KeyOnPress(GLFWwindow *_Window, int _Key)
{
	static bool Prev;
	bool Curr = false;
	Curr = KeyDown(_Window, _Key);
	if ((!Prev) && (Curr))
	{
		Prev = Curr;
		return true;
	}
	Prev = Curr;
	return false;
}