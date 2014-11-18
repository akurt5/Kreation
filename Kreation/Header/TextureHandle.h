#ifndef TEXTURE_H
#define TEXTURE_H

#include "SOIL.h"
#include "PolygonHandle.h"

class Tex
{
public:

	GLuint Material;
			//unsigned int Image;
	float *Pixels;
	
	bool Load(char *_Path, int _Width, int _Height);// need to work a function tht takes in "MipMap = false" and sets mipmapping to off. dynamic as, insead of FUNC(NULL, NULL, NULL, stuff, NULL);
	bool Update();
	//bool Move(glm::vec3 _Pos);
	//bool Rotate(float _Angle);
	//bool Draw();
};

#endif 

