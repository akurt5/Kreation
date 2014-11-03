#include "PolygonHandle.h"
#include <iostream>


template <typename Enum>

bool Poly::Create(Enum _Size, float _Radius, bool _CentreIsCentre, glm::vec3 _Position)
{
	static_assert(std::is_enum<Enum>::value, "Only enums are allowed here");//pretty much throws an error if you break the rules. i think.
	
	VBO = 0;
	glGenVertexArrays (1, &VBO);//gen the empty VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind it to OpenGL
	glBufferData(GL_ARRAY_BUFFER, _Size * sizeof (float), CalcPoints(_Size, _Position, _Radius), GL_STATIC_DRAW);// there is '_Size' number of floats and they are located at points.

	VAO = 0;
	glGenVertexArrays (1, &VAO);//gen empty VAO
	glBindVertexArray (VAO);// Bind to OGL
	glEnableVertexAttribArray (0);//info is at VBO location 0
	glBindBuffer (GL_ARRAY_BUFFER, VBO);// Bind more shit
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//defines the layout of our first vertex buffer

	/*const char* vertex_shader =
	"#version 400\n"
	"in vec3 vp;"
	"void main () {"
	"  gl_Position = vec4 (vp, 1.0);"
	"}";

	const char* fragment_shader =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main () {"
	"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
	"}";*/

	//Do i load the shaders here or do i load them in the main?

	//eg	LoadSprite(path, size, shaderpaths)
	//or
	//		LoadShaders(shaders)
	//		LoadSprite(path, size, shaders)
	return true;
}
bool Poly::Update()
{
		return true;
}
bool Poly::Draw()
{
		return true;
}
float *Poly::CalcPoints(int _Size, glm::vec3 _Centre, float _Radius, float _AngleOffset)
{
	int i;//iterator for upcoming while loop
	if(_Size <= QUATTUOR)
	{                        /*0,1,2,3,4,5,6,7,8,9*/
		Points[(_Size * 10)];/*x,y,z,r,g,b,a,u,v,w*/
		i = 0;// if we are making a quad or tri then we need no center vert.
	}
	else
	{
		Points[(_Size +1)* 10];//extra set is for center vert.
		Points[(_Size * 9)] = _Centre.x;//X value for center		// 3* 10 = 30 + 1,2 or 3 == >30. thats why we use 9 here.
		Points[(_Size * 9)+1] = _Centre.y;//Y value for center
		Points[(_Size * 9)+2] = _Centre.z;//Z center
		i = 9;//centre vert will be skipped in for loop now because it in not common between quad/tri and pent etc.
	}
	
	float Angle = _AngleOffset;//while this is zero there will always be a vertex pointing straight up. even for quads. 
	float DiffAngle = 360 / _Size;
	while (i<_Size)//WOW!, while loop. We're in trouble.
		{
			glm::vec2 PointPos = Pythag(Angle, _Radius);//converts polar coords of point to cartesian.
			Angle += DiffAngle;
			Points[i++] = PointPos.x + _Centre.x;
			Points[i++] = PointPos.y + _Centre.y;
			Points[i++] = _Centre.z;
			i+=8;//this will round up the iterator to assure we are only assigning to x,y,z each loop.
		}//points should be generated in a clockwise fashion.

	return Points;
}
glm::vec2 Poly::Pythag(float _Angle, float _Radius)
{
	glm::vec2 Pos;
	Pos.x = _Radius * cos(_Angle);
	Pos.y = _Radius * sin(_Angle);
	return Pos;
}