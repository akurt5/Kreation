#ifndef POLY_H_
#define POLY_H_

#include "GL/glew.h"
#include "ShaderHandle.h"
#include <stdarg.h>
#include "PolyData.h"
#include "GLM/ext.hpp"



class Poly
{
public:

	float *VertData;
	template <typename Enum>
	bool Create(Enum _Size, float _Radius, bool _CentreIsCentre, glm::vec3 _Position);
	bool Update();
	bool Draw();
	
private:
	float *CalcPoints(int _Size, glm::vec3 _Centre, float _Radius, float _AngleOffset = 90.0f);
	glm::vec2 Pythag(float _Angle, float _Radius);
	
};

#endif