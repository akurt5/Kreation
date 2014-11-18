#ifndef SPRITE_H
#define SPRITE_H

#include "GL/glew.h"

#include "PolygonHandle.h"
#include "TextureHandle.h"
#include "ShaderHandle.h"

class Sprite : public ShaderUse
{
public:

	
	Sprite(int _Size, float _Radius, bool _CentreIsCentre, glm::vec3 _Position);
	bool Update();
	bool Draw();

	bool Move();
	bool Rotate();

	Poly Polygon;
	Tex Material;

	unsigned int Position, UVCoords;

};

#endif