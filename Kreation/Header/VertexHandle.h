#ifndef VERTEX_H
#define VERTER_H

#include "glm\ext.hpp"

class Vertex
{
public:

	float U, V, X, Y, Z, R, G, B, A;
	
	operator glm::vec2();
	operator glm::vec3();
	operator glm::vec4();

	Vertex operator = (const glm::vec2 _Vec2);
	Vertex operator = (const glm::vec3 _Vec2);
	Vertex operator = (const glm::vec4 _Vec2);
};

#endif

