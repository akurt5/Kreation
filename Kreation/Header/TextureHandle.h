#ifndef TEXTURE_H
#define TEXTURE_H

#include "SOIL.h"
#include "PolygonHandle.h"

class Texture
{
public:

	Poly Polygon;
	GLuint Material;
	unsigned char *Image;
	float *Pixels;

	bool Load(char *_Path, int _Width, int _Height);
	bool Update(Shader _ShaderProgram);
	bool Move(glm::vec3 _Pos);
	bool Rotate(float _Angle);
	bool Draw();
};

#endif 

