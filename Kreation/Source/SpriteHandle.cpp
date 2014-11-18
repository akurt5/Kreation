#include "SpriteHandle.h"


Sprite::Sprite(int _Size, float _Radius, bool _CentreIsCentre, glm::vec3 _Position)
{
	Polygon.Create(_Size, _Radius, _CentreIsCentre, _Position);

	

	//Polygon.CreateCleanUp();

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

