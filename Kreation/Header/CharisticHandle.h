#ifndef CHARISTIC_H
#define CHARISTIC_H

#include "glm/glm.hpp"
//#include <vector>
#include <string>
#include <map>

template<class _Container>class Charistic//										CBF typing Characteristic fully. And so it was crafted. 
//							Characteristics define an object.
//							Objects can have an unlimited number of Charistics
//							Work out a way to make these bastards at runtime
{
public:
	//Charistic(char* _Name, void *_Container);//void pointers are very inneficient

	//Template function add whatever datatype here.
	Charistic(std::string *_Name, _Container *_DataType);
	//void *Container;//								e.g. Vec3  or  int  or  float
	_Container *Container;
	std::string *Name;//									e.g. Position  or  Verts  or  Texture  or  Model
	
};

//														-------------------Normal Var Types
															

#endif

