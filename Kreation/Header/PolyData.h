#include "GL/glew.h"

namespace
{
	//typedef unsigned int Enum;// i want this to eplace the Enum templates above funtion calls
	enum 
	{
		TRES		= 3,
		QUATTUOR	= 4,
		QUINQUE		= 5,
		SEX			= 6,
		SEPTEM		= 7,
		OCTO		= 8,
		NOVEM		= 9,
		DECEM		= 10
	}PolySize;

	GLuint VBO, VAO, IBO;
}