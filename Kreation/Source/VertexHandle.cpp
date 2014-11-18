#include "VertexHandle.h"


	Vertex::operator glm::vec2() 
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
	Vertex Vertex::operator = (const glm::vec2 _Vec2)
	{
		Vertex Vert;
		Vert.U = _Vec2.x;
		Vert.V = _Vec2.y;
		return Vert;
	}
	Vertex Vertex::operator = (const glm::vec3 _Vec2)
	{
		Vertex Vert;
		Vert.X = _Vec2.x;
		Vert.Y = _Vec2.y;
		Vert.Z = _Vec2.z;
		return Vert;
	}
	Vertex Vertex::operator = (const glm::vec4 _Vec2)
	{
		Vertex Vert;
		Vert.R = _Vec2.r;
		Vert.G = _Vec2.g;
		Vert.B = _Vec2.b;
		Vert.A = _Vec2.a;
		return Vert;
	}