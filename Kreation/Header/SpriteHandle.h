#ifndef SPRITE_H
#define SPRITE_H

#include "GL/glew.h"
#include "PolygonHandle.h"
#include "TextureHandle.h"

class Sprite //: public ShaderUse
{
public:

	Sprite(int _Sides, float _Radius, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation);
	Sprite(char *_Path, int _Sides, float _Radius, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation);
	Sprite(int _Sides, glm::vec2 _Dimensions, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation);
	Sprite(char *_Path, int _Sides, glm::vec2 _Dimensions, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation);

	bool Update();
	bool Draw();

	bool Move();
	bool Rotate();

	Poly Polygon;
	Tex Material;

	unsigned int Position, UVCoords;

};

#endif