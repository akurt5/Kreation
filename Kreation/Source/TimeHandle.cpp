#include "TimeHandle.h"
#include "GLFW/glfw3.h"

double Time::GetTime()
{
	CurrentTime = NULL;
	CurrentTime = glfwGetTime();
	if(!CurrentTime)
	{return 0;}
	return CurrentTime;
}
bool Time::Update()
{
	Delta = CurrentTime;
	Delta = GetTime() - Delta;
	return true;
}