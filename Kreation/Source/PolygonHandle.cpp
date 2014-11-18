#include "PolygonHandle.h"
#include "PolyData.h"
#include <iostream>


template <typename Enum>

bool Poly::Create(Enum _Size, float _Radius, bool _CentreIsCentre, glm::vec3 _Position)
{
	static_assert(std::is_enum<Enum>::value, "Only enums are allowed here");//pretty much throws an error if you break the rules. i think.
	
	VBO = 0;
	glGenVertexArrays (1, &VBO);//gen the empty VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind it to OpenGL //send to GPU
	glBufferData(GL_ARRAY_BUFFER, _Size * sizeof (Vertex), CalcPoints(_Size, _Position, _Radius), GL_DYNAMIC_DRAW);// there is '_Size' number of floats and they are located at VertData.
	//GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the world).
	//GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
	//GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
	VAO = 0;
	glGenVertexArrays (1, &VAO);//gen empty VAO
	glBindVertexArray (VAO);// Bind to OGL
	glEnableVertexAttribArray (0);//info is at VBO location 0
	glBindBuffer (GL_ARRAY_BUFFER, VBO);// Bind more shit
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//defines the layout of our first vertex buffer

	IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Size * sizeof (unsigned int), CalcIndices(_Size), GL_STATIC_DRAW);

	//Set Up Vertex Arrays
	glEnableVertexAttribArray(0);//Vertex position will be attrib 0
	glVertexAttribLPointer(0, _Size, GL_FLOAT, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);//Texture UV coords numbered 1
	glVertexAttribLPointer(1, _Size, GL_FLOAT, sizeof(glm::vec3), (void*)16);//why is lukes (void*)16

	glBindVertexArray(0);	//VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//IBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] Indices;
	delete[] VertData;

	//Do i load the shaders here or do i load them in the main?

	//eg	LoadSprite(path, size, shaderpaths)
	//or
	//		LoadShaders(shaders)				//I like this more because it seems like you could have nice sections where different shaders are used
	//		LoadSprite(path, size, shaders)
	return true;
}
bool Poly::Update()
{
	return true;
}
unsigned int *Poly::CalcIndices(int _Size)//Make a function for this
{
	/*if(_Size > QUATTUOR)
	{

	}
	else
	{
		int Iterator = 0;
		do{

		} while (Iterator);
	}*/

	switch(_Size)
	{
	case TRES:
		//This TRI will use one poly.
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;
			break;
	case QUATTUOR:
		//Quads are made up of 2 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;
		//Here is the second
		Indices[3] = 0;
		Indices[4] = 2;
		Indices[5] = 3;
			break;
	case QUINQUE:
		//five sided Poly. 6 verts. 5 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 5;
		//Second Poly
		Indices[3] = 1;
		Indices[4] = 2;
		Indices[5] = 5;
		//Third
		Indices[6] = 2;
		Indices[7] = 3;
		Indices[8] = 5;
		//Fourth
		Indices[9] = 3;
		Indices[10] = 4;
		Indices[11] = 5;
		//Fifth
		Indices[12] = 4;
		Indices[13] = 0;
		Indices[14] = 5;
			break;
	case SEX:
		//Six sided Poly. 7 verts. 6 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 6;
		//Second Poly
		Indices[3] = 1;
		Indices[4] = 2;
		Indices[5] = 6;
		//Third
		Indices[6] = 2;
		Indices[7] = 3;
		Indices[8] = 6;
		//Fourth
		Indices[9] = 3;
		Indices[10] = 4;
		Indices[11] = 6;
		//Fifth
		Indices[12] = 4;
		Indices[13] = 5;
		Indices[14] = 6;
		//Sixth
		Indices[15] = 5;
		Indices[16] = 0;
		Indices[17] = 6;
			break;
	case SEPTEM:
		//Seven sided Poly. 8 verts. 7 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 7;
		//Second Poly
		Indices[3] = 1;
		Indices[4] = 2;
		Indices[5] = 7;
		//Third
		Indices[6] = 2;
		Indices[7] = 3;
		Indices[8] = 7;
		//Fourth
		Indices[9] = 3;
		Indices[10] = 4;
		Indices[11] = 7;
		//Fifth
		Indices[12] = 4;
		Indices[13] = 5;
		Indices[14] = 7;
		//Sixth
		Indices[15] = 5;
		Indices[16] = 6;
		Indices[17] = 7;
		//Seventh
		Indices[18] = 6;
		Indices[19] = 0;
		Indices[20] = 7;
			break;
	case OCTO:
		//Eight sided Poly. 9 verts. 8 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 8;
		//Second Poly
		Indices[3] = 1;
		Indices[4] = 2;
		Indices[5] = 8;
		//Third
		Indices[6] = 2;
		Indices[7] = 3;
		Indices[8] = 8;
		//Fourth
		Indices[9] = 3;
		Indices[10] = 4;
		Indices[11] = 8;
		//Fifth
		Indices[12] = 4;
		Indices[13] = 5;
		Indices[14] = 8;
		//Sixth
		Indices[15] = 5;
		Indices[16] = 6;
		Indices[17] = 8;
		//Seventh
		Indices[18] = 6;
		Indices[19] = 7;
		Indices[20] = 8;
		//Eighth
		Indices[21] = 7;
		Indices[22] = 0;
		Indices[23] = 8;
			break;
	case NOVEM:
		//Nine sided Poly. 10 verts. 9 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 9;
		//Second Poly
		Indices[3] = 1;
		Indices[4] = 2;
		Indices[5] = 9;
		//Third
		Indices[6] = 2;
		Indices[7] = 3;
		Indices[8] = 9;
		//Fourth
		Indices[9] = 3;
		Indices[10] = 4;
		Indices[11] = 9;
		//Fifth
		Indices[12] = 4;
		Indices[13] = 5;
		Indices[14] = 9;
		//Sixth
		Indices[15] = 5;
		Indices[16] = 6;
		Indices[17] = 9;
		//Seventh
		Indices[18] = 6;
		Indices[19] = 7;
		Indices[20] = 9;
		//Eighth
		Indices[21] = 7;
		Indices[22] = 8;
		Indices[23] = 9;
		//Ninth
		Indices[21] = 8;
		Indices[22] = 0;
		Indices[23] = 9;
			break;
	case DECEM:
		//Ten sided Poly. 11 verts. 10 TRIs
		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 10;
		//Second Poly
		Indices[3] = 1;
		Indices[4] = 2;
		Indices[5] = 10;
		//Third
		Indices[6] = 2;
		Indices[7] = 3;
		Indices[8] = 10;
		//Fourth
		Indices[9] = 3;
		Indices[10] = 4;
		Indices[11] = 10;
		//Fifth
		Indices[12] = 4;
		Indices[13] = 5;
		Indices[14] = 10;
		//Sixth
		Indices[15] = 5;
		Indices[16] = 6;
		Indices[17] = 10;
		//Seventh
		Indices[18] = 6;
		Indices[19] = 7;
		Indices[20] = 10;
		//Eighth
		Indices[21] = 7;
		Indices[22] = 8;
		Indices[23] = 10;
		//Ninth
		Indices[21] = 8;
		Indices[22] = 9;
		Indices[23] = 10;
		//Tenth
		Indices[21] = 9;
		Indices[22] = 0;
		Indices[23] = 10;
			break;
	};
	return Indices;
}
Vertex *Poly::CalcPoints(int _Size, glm::vec3 _Centre, float _Radius, float _AngleOffset)
{
	int i;//iterator for upcoming while loop
	if(_Size <= QUATTUOR)
	{                        /*0,1,2,3,4,5,6,7,8*/
		//VertData[(_Size * 9)];/*x,y,z,r,g,b,a,u,v*/
		VertData[_Size];
		i = 0;// if we are making a quad or tri then we need no center vert.
	}
	else
	{
		i = 9;//centre vert will be skipped in for loop now because it in not common between quad/tri and pent etc.
		VertData[_Size +1];
		VertData[0] = _Centre;
		i=1;
	}
	
	float Angle = _AngleOffset;//while this is zero there will always be a vertex pointing straight up. !!even for quads.!! 
	float DiffAngle = 360 / _Size;
	while (i<_Size)//WOW!, while loop. We're in trouble.
		{
			glm::vec2 PointPos = Pythag(Angle, _Radius);//converts polar coords of point to cartesian.
			Angle += DiffAngle;
			VertData[i].X = PointPos.x + _Centre.x;
			VertData[i].Y = PointPos.y + _Centre.y;
			VertData[i].Z = _Centre.z;
			i++;//this will round up the iterator to assure we are only assigning to x,y,z each loop.
		}//points should be generated in a clockwise fashion.

	return VertData;
}
glm::vec2 Poly::Pythag(float _Angle, float _Radius)
{
	glm::vec2 Pos;
	Pos.x = _Radius * cos(_Angle);
	Pos.y = _Radius * sin(_Angle);
	return Pos;
}