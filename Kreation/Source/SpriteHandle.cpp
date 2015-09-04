#include "SpriteHandle.h"
#include "GLFW/glfw3.h"
#include "PolyData.h"


Sprite::Sprite(int _Sides, float _Radius, bool _CentreIsCentre, glm::vec3 _Position, float _Rotation)
{
	Polygon.Create(_Sides, _Radius, _CentreIsCentre, _Position, _Rotation);
}
Sprite::Sprite(char * _Path, int _Sides, float _Radius, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation)
{
	Sprite(_Sides, _Radius, _CentreIsCentre, _Position, _Rotation);
	Material.Load(_Path, _Radius, _Radius);
}
Sprite::Sprite(int _Sides, glm::vec2 _Dimensions, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation)
{
	
}
Sprite::Sprite(char *_Path, int _Sides, glm::vec2 _Dimensions, bool _CentreIsCentre, glm::vec3 _Position,  float _Rotation)
{

}
bool Sprite::Update()
{
	return true;
}
bool Sprite::Draw()
{

	return true;
}
bool Sprite::Move()
{
	return true;
}
bool Sprite::Rotate()
{
	return true;
}

