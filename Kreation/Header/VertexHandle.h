#ifndef VERTEX_H
#define VERTER_H

#include "glm\ext.hpp"

class Vertex//--------------Entire class under constant review, is this class and its members(vars and funcs) a random erection in the life of my code?
{
public:

	float /*U, V,*/ X, Y, Z/*, R, G, B, A*/;
	
	//operator glm::vec2();
	operator glm::vec3();
	//operator glm::vec4();

	/*glm::vec2 UV();
	void UVadd(glm::vec2 _Vec2);
	void UVequals(glm::vec2 _Vec2);*/
	glm::vec3 XYZ();
	void XYZadd(glm::vec3 _Vec3);
	void XYZequals(glm::vec3 _Vec3);
	/*glm::vec4 RGBA();
	void RGBAadd(glm::vec4 _Vec4);
	void RGBAequals(glm::vec4 _Vec4);*/

	//Vertex operator = (const glm::vec2 _Vec2);
	Vertex operator = (const glm::vec3 _Vec3);
	//Vertex operator = (const glm::vec4 _Vec4);
};

#endif

