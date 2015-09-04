#include "PolygonHandle.h"
#include "GL/glew.h"
#include "MiscMath.h"
#include "PolyData.h"

#include <iostream>

bool Poly::InitialiseCharistics()//needs to be template func
{
	//AddCharistic()
	Charistics
}
bool Poly::Create(int _Sides, glm::vec2 _Dimensions, bool _CentreIsCentre, glm::vec3 _Position, float _AngleOffset)
{
	//VertData = new Vertex();
	//Indices = new unsigned int();

	VBO = 0;
	glGenVertexArrays (1, &VBO);//gen the empty VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind it to OpenGL //send to GPU
	glBufferData(GL_ARRAY_BUFFER, /*(_Size * sizeof (Vertex))*/(_Sides * 3)*sizeof(float), CalcPoints(_Sides, _Dimensions, _Position, _AngleOffset), GL_DYNAMIC_DRAW);// there is '_Size' number of floats and they are located at VertData. _Size * sizeof (Vertex) = in bytes the size.
	//GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the Environment).
	//GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
	//GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
	VAO = 0;
	glGenVertexArrays (1, &VAO);//gen empty VAO
	glBindVertexArray (VAO);// Bind to OGL
	glEnableVertexAttribArray (0);//info is at VBO location 0
	glBindBuffer (GL_ARRAY_BUFFER, VBO);// Bind more shit
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//defines the layout of our first vertex buffer

	/*IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Sides * sizeof (unsigned int), CalcIndices(_Sides), GL_STATIC_DRAW);

	//Set Up Vertex Arrays
	glEnableVertexAttribArray(0);//Vertex position will be attrib 0
	glVertexAttribLPointer(0, _Sides, GL_FLOAT, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);//Texture UV coords numbered 1
	glVertexAttribLPointer(1, _Sides, GL_FLOAT, sizeof(glm::vec3), (void*)16);//why is lukes (void*)16

	glBindVertexArray(0);	//VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	//IBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	//delete[] Indices;
	//for each ( Vertex i in VertData[] )
//		delete[] VertData;

	//Do i load the shaders here or do i load them in the main?

	//eg	LoadSprite(path, size, shaderpaths)
	//or
	//		LoadShaders(shaders)				//I like this more because it seems like you could have nice sections where different shaders are used
	//		LoadSprite(path, size, shaders)
	return true;
}
bool Poly::Create(int _Sides, float _Radius, bool _CentreIsCentre, glm::vec3 _Position, float _AngleOffset)
{
	float Diameter = _Radius * 2;
	return Create(_Sides, glm::vec2(Diameter, Diameter), _CentreIsCentre, _Position, _AngleOffset);//CentreIsCentre don't work!
}
bool Poly::Create(int _Sides, float *_Verts, bool _CentreIsCentre, glm::vec3 _Position, float _AngleOffset)
{
	VBO = 0;
	glGenVertexArrays (1, &VBO);//gen the empty VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind it to OpenGL //send to GPU
	glBufferData(GL_ARRAY_BUFFER, /*(_Size * sizeof (Vertex))*/(_Sides * 3) * sizeof(float), _Verts, GL_DYNAMIC_DRAW);// there is '_Size' number of floats and they are located at VertData. _Size * sizeof (Vertex) = in bytes the size.
	//GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the Environment).
	//GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
	//GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
	VAO = 0;
	glGenVertexArrays (1, &VAO);//gen empty VAO
	glBindVertexArray (VAO);// Bind to OGL
	glEnableVertexAttribArray (0);//info is at VBO location 0
	glBindBuffer (GL_ARRAY_BUFFER, VBO);// Bind more shit
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//defines the layout of our first vertex buffer
	return true;
}
bool Poly::Create(int _Sides, glm::vec3 *_Verts, bool _CentreIsCentre, glm::vec3 _Position, float _AngleOffset)
{
	VBO = 0;
	glGenVertexArrays (1, &VBO);//gen the empty VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind it to OpenGL //send to GPU
	glBufferData(GL_ARRAY_BUFFER, /*(_Size * sizeof (Vertex))*/(_Sides * 3) * sizeof(glm::vec3), _Verts, GL_DYNAMIC_DRAW);// there is '_Size' number of floats and they are located at VertData. _Size * sizeof (Vertex) = in bytes the size.
	//GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the Environment).
	//GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
	//GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
	VAO = 0;
	glGenVertexArrays (1, &VAO);//gen empty VAO
	glBindVertexArray (VAO);// Bind to OGL
	glEnableVertexAttribArray (0);//info is at VBO location 0
	glBindBuffer (GL_ARRAY_BUFFER, VBO);// Bind more shit
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//defines the layout of our first vertex buffer
	return true;
}
bool Poly::Update()
{
	return true;
}
bool Poly::Draw(Shader _Shader)
{
		glUseProgram (_Shader.ShaderProgram);
		glBindVertexArray (VAO);
		glDrawArrays (GL_TRIANGLES, 0, 3);

	return true;
}
bool Poly::Move(glm::vec3 _Position)
{
	return true;
}
bool Poly::Rotate(float _Degrees)
{
	return true;
}
unsigned int Poly::CalcIndices(int _Sides)
{
	//unsigned int TempIndices[6];// If tri or quad: size = poly count * 3. If  larger size = vert count * 3
	/*if(_Sides < FIVE)
	{
		//This TRI will use one poly.
		TempIndices[0] = (unsigned int)0;
		TempIndices[1] = (unsigned int)1;

		if(_Sides == FOUR)//if it's not a tri we want to change the last indice
		{
			TempIndices[2] = (unsigned int)3;//			If QUAD: we want this indice

		//Quads are made up of 2 TRIs
		
			TempIndices[3] = (unsigned int)0;
			TempIndices[4] = (unsigned int)2;
			TempIndices[5] = (unsigned int)3;

		}
		else
		{
			TempIndices[2] = (unsigned int)2;//			Else TRI: as you were 
		}
	}
	else
	{*/
		int Iterator = 0;
		do{

			/*TempIndices[Iterator] = (unsigned int)Iterator;
			Iterator ++;//0, 3, 6, 9, 12, 15, 18, 21.
			TempIndices[Iterator] = (unsigned int)Iterator;
			Iterator ++;//1, 4, 7, 10, 13, 16, 19, 22.
			TempIndices[Iterator] = (unsigned int)_Sides;
			Iterator ++;//2, 5, 8, 11, 14, 17, 20, 23.*/

			Indices.emplace_back(0);
			Indices.emplace_back(Iterator += 1);
			Indices.emplace_back(Iterator += 1);	

		//} while ( Iterator != (_Sides * 3));
		}while(Iterator != (_Sides - 2));
	//}

	//Indices = &TempIndices[0];

	return Indices[0];
}
Vertex *Poly::CalcPoints(int _Sides, glm::vec3 _Centre, float _Radius, float _AngleOffset)
{
	float Diameter = _Radius * 2;
	return CalcPoints(_Sides, glm::vec2 (Diameter, Diameter), _Centre, _AngleOffset);
}
Vertex *Poly::CalcPoints(int _Sides, glm::vec2 _Dimensions, glm::vec3 _Centre, float _AngleOffset)
	//draw an elipse you fucking badger, you're already using a circle above. its the first thing you shouldve thought about.
	//i respect that you never thought of it as a cirlce as much as i loathe it though. get shit together.
{
	Vertex TempVert;
	glm::vec2 HalfDimensions = glm::vec2 (_Dimensions.x * 0.5, _Dimensions.y * 0.5);
	int i = 0;//iterator for upcoming while loop
	/*if(_Sides <= FOUR)
	{
		i = 0;// if we are making a quad or tri then we need no center vert.
	}
	else
	{
		TempVert.XYZequals(_Centre);//otherwise the centre goes here
		VecVertData.emplace_back(TempVert);
		i = 1;
	}*/
	
	float Angle = _AngleOffset;//while this is zero there will always be a vertex pointing straight up. !!even for quads.!! 
	float DiffAngle = 360.0f / _Sides, DimensionDiff = 0;
	glm::vec2 PointPos;
	while (i<_Sides)//WOW!, while loop. We're in trouble.(Round-a-bout music - cameveryday)
		{
			/*if((int)Angle % 90 == 0)  
			{
				if((int)Angle % 180 == 0)
			}*/
			if(HalfDimensions.y != HalfDimensions.x) // get the difference between the width and height. if there is one.
			{
				if(HalfDimensions.y > HalfDimensions.x)
				{
					DimensionDiff = HalfDimensions.y - HalfDimensions.x;
				}
				else
				{
					DimensionDiff = HalfDimensions.x - HalfDimensions.y;
				}
				DimensionDiff /= 90;// 90 is becasue we are calculating everything in a single quadrant. Dimension * diff gives the right length to have properly stretched shapes.
			}

			if((Angle == 0) || (Angle == 180) || (Angle == 360))//If the triangle is so thin its actually a line this won't work.
			{
				if(Angle == 180)
				{
					PointPos = glm::vec2(0, -HalfDimensions.y);
				}
				PointPos = glm::vec2(0, HalfDimensions.y);

			}
	   else if((Angle == 90) || (Angle == 270))//Same goes here
			{
				if(Angle == 270)
				{
					PointPos = glm::vec2(-HalfDimensions.x, 0);
				}
				PointPos = glm::vec2(HalfDimensions.x, 0);
			}
	   else
			{
				//if(PointPos == glm::vec2(0,0))//If its the first vertex
				//{
				//	PointPos = glm::vec2(HalfWidth * cos(MiscMath::DegToRad(Angle)), HalfHeight * sin(MiscMath::DegToRad(Angle)));//converts polar coords of point to cartesian.
				//}
				//else
				{
					float PracticeAngle = Angle, LengthAddition = DimensionDiff * PracticeAngle;
					int Quadrant = 0;
					while(PracticeAngle > 90)
					{
						PracticeAngle -= 90;
						Quadrant ++;
					}
					float PX = HalfDimensions.x + LengthAddition, PY = HalfDimensions.y + LengthAddition, PA = MiscMath::DegToRad(PracticeAngle);
					PointPos = glm::vec2(PX * sin(PA), PY * cos(PA));
					glm::vec2 TempPointPos = PointPos;
					switch (Quadrant)//inverse and switch the coordinates so that it rotates the point 90 degrees (to the next quadrant.
					{
					case 0:
						//If it's in the first quadrand than all is well
						break;
					case 1:

						
						PointPos.x = -TempPointPos.y;
						PointPos.y = TempPointPos.x;

						break;
					case 2:

						PointPos.x = -TempPointPos.y;
						PointPos.y = -TempPointPos.x;

						break;
					case 3:

						PointPos.x = TempPointPos.y;
						PointPos.y = -TempPointPos.x;

						break;
					};
				}
			}
	   TempVert.XYZequals(glm::vec3(_Centre.x + PointPos.x, _Centre.y + PointPos.y, _Centre.z));
	   VecVertData.emplace_back(TempVert);
	   Angle += DiffAngle;

			i++;//this will round up the iterator to assure we are only assigning to x,y,z each loop.
		}//points should be generated in a clockwise fashion.
	Position = _Centre;
	//Vertex *VertData = &VecVertData[0];
	//return VertData;
	return &VecVertData[0];
}

