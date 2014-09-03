#ifndef CHARISTIC_H
#define CHARISTIC_H

#include "glm.hpp"
#include <vector>
//														-------------------Forward Declares
class Object;

class Charistic//										CBF typing Characteristic fully. And so it was crafted. 
//							Characteristics define an object.
//							Objects can have an unlimited number of Charistics
//							Work out a way to make these bastards at runtime
{
public:
	//Charistic(char* _Name, void *_Container);//void pointers are very inneficient
	Charistic(char *_Name);
	//void *Container;//								e.g. Vec3  or  int  or  float
	Charistic *Container;
	char *Name;//									e.g. Position  or  Verts  or  Texture  or  Model
	
};

/*class Char_List
//							CharList will hold the Characteristics of each object
//							for each derivative class of Charistic you will NEED and operator overload
{
	void Add(Charistic *_Characteristic, ...);//			Add should check for duplicates first
	void Remove(char* _Name, ...);//						Remove should have a safe guard
	std::vector<Charistic*> Charistics;

	inline int operator[](char *_Name);
};*/
//														-------------------Normal Var Types
class Int_Charistic : public Charistic //Integer Charistic. Add an Integer to your Object.
{
	Int_Charistic(char *_Name, int _Value) : Charistic(_Name)
	{

	}


	int Value;
};
class UInt_Charistic : public Charistic //Unsigned Integer Charistic. Add an Unsigned Integer to your Object.
{
	UInt_Charistic(unsigned int _Value);

	unsigned int Value;
};
class Float_Charistic : public Charistic //Floating point Charistic. Add a Float to your Object.
{
	Float_Charistic(float _Value);

	float Value;
};
class Double_Charistic : public Charistic //Double Charistic. Add a Double to your Object.
{
	Double_Charistic(double _Value);

	double Value;
};
class Char_Charistic : public Charistic //Char Charistic. Add a Char to your Object.
{
	Char_Charistic(char *_String);

	char *String;
};
//														-------------------GLM Var Types
class Vec2_Charistic : public Charistic // 2D Vector Charistic. Add a Vec2 to your Object.
{
	Vec2_Charistic(glm::vec2 _Vector2);

	glm::vec2 Vector2;
};
class Vec3_Charistic : public Charistic // 3D Vector Charistic. Add a Vec3 to your Object.
{
	Vec3_Charistic(glm::vec3 _Vector3);

	glm::vec3 Vector3;
};
class Vec4_Charistic : public Charistic // 4D Vector Charistic. Add a Vec4 to your Object.
{
	Vec4_Charistic(glm::vec4 _Vector4);

	glm::vec4 Vector4;
};
class Mat3_Charistic : public Charistic
{
	Mat3_Charistic(glm::mat3 *_Matrix);

	glm::mat3 *Matrix;
};
class Mat4_Charistic : public Charistic
{
	Mat4_Charistic(glm::mat4 *_Matrix);

	glm::mat4 *Matrix;
};
//														-------------------Kurt5 Var Types
class Object_Charistic : public Charistic//Object Charistic. Add an Object to your Object.
{
	Object_Charistic(Object *_Obj);
	Object *Obj;
};

#endif

