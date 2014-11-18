#ifndef POLY_H_
#define POLY_H_

#include "GL/glew.h"
#include <stdarg.h>
#include "GLM/ext.hpp"
#include "VertexHandle.h"


class Poly
{
public:
	unsigned int *Indices;
	Vertex *VertData;
	//float *VertData;
	template <typename Enum>
	bool Create(Enum _Size, float _Radius, bool _CentreIsCentre, glm::vec3 _Position);
	bool Update();
	//bool CreateCleanUp();
	
private:
	
	unsigned int *CalcIndices(int _Size);
	Vertex *CalcPoints(int _Size, glm::vec3 _Centre, float _Radius, float _AngleOffset = 90.0f);
	//float *CalcPoints(int _Size, glm::vec3 _Centre, float _Radius, float _AngleOffset = 90.0f);
	glm::vec2 Pythag(float _Angle, float _Radius);
	
};

#endif