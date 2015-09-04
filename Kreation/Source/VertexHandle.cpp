#include "VertexHandle.h"


	/*Vertex::operator glm::vec2() 
	{
		return glm::vec2(U, V);
	}
	Vertex::operator glm::vec3() 
	{
		return glm::vec3(X, Y, Z);
	}
	Vertex::operator glm::vec4() 
	{
		return glm::vec4(R, G, B, A);
	}

	glm::vec2 Vertex::UV()
	{
		return glm::vec2(U, V);
	}
	void Vertex::UVadd(glm::vec2 _Vec2)
	{
		U += _Vec2.x;
		V += _Vec2.y;
	}
	void Vertex::UVequals(glm::vec2 _Vec2)
	{
		U = _Vec2.x;
		V = _Vec2.y;
	}*/
	glm::vec3 Vertex::XYZ()
	{
		return glm::vec3(X, Y, Z);
	}
	void Vertex::XYZadd(glm::vec3 _Vec3)
	{
		X += _Vec3.x;
		Y += _Vec3.y;
		Z += _Vec3.z;
	}
	void Vertex::XYZequals(glm::vec3 _Vec3)
	{
		X = _Vec3.x;
		Y = _Vec3.y;
		Z = _Vec3.z;
	}
	/*glm::vec4 Vertex::RGBA()
	{
		return glm::vec4(R, G, B, A);
	}
	void Vertex::RGBAadd(glm::vec4 _Vec4)
	{
		R += _Vec4.r;
		G += _Vec4.g;
		B += _Vec4.b;
		A += _Vec4.a;
	}
	void Vertex::RGBAequals(glm::vec4 _Vec4)
	{
		R = _Vec4.r;
		G = _Vec4.g;
		B = _Vec4.b;
		A = _Vec4.a;
	}

	Vertex Vertex::operator = (const glm::vec2 _Vec2)
	{
		Vertex Vert;
		Vert.U = _Vec2.x;
		Vert.V = _Vec2.y;
		return Vert;
	}*/
	Vertex Vertex::operator = (const glm::vec3 _Vec3)
	{
		Vertex Vert;
		Vert.X = _Vec3.x;
		Vert.Y = _Vec3.y;
		Vert.Z = _Vec3.z;
		return Vert;
	}
	/*Vertex Vertex::operator = (const glm::vec4 _Vec4)
	{
		Vertex Vert;
		Vert.R = _Vec4.r;
		Vert.G = _Vec4.g;
		Vert.B = _Vec4.b;
		Vert.A = _Vec4.a;
		return Vert;
	}*/