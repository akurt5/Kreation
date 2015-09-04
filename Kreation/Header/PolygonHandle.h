#ifndef POLY_H
#define POLY_H

#include <vector>
#include <stdarg.h>
#include "GLM/ext.hpp"
#include "VertexHandle.h"
#include "ShaderHandle.h"
#include "Object.h"

class Poly : public ShaderControl, public Object
{
public:
	//unsigned int *Indices;
	std::vector<unsigned int> Indices;



	std::vector<Vertex> VecVertData;
	Vertex *VertData;

	//Position is the centre of the polygon. 
	//If you say so, that is.

	GLuint VBO, VAO, IBO;

	bool InitialiseCharistics();

	//Creates an eliptical Polygon with the specified number of _Sides.
	//The _Dimensions of the elipse.
	//Were _CentreIsCentre lets you select either the centre or top left corner as the point of reference (CentreOfMass).
	//The Polygons worldspace coordinates can be specifyied with _Position.
	//_AngleOffset indicates the rotation (around the Z axis) of the Polygon. Defaulted to 45 degrees.
	bool Create(int _Sides, glm::vec2 _Dimensions, bool _CentreIsCentre, glm::vec3 _Position, float _AngleOffset = 45.0f);
	
	//Creates a circular Polygon with the specified number of _Sides.
	//The _Radius of the circle.
	//Were _CentreIsCentre lets you select either the centre or top left corner as the point of reference (CentreOfMass).
	//The Polygons worldspace coordinates can be specifyied with _Position.
	//_AngleOffset indicates the rotation (around the Z axis) of the Polygon. Defaulted to 45 degrees.
	bool Create(int _Sides, float _Radius, bool _CentreIsCentre, glm::vec3 _Position, float _AngleOffset = 45.0f);
	
	//Creates a Polygon with the specified _Verts.
	//Were _CentreIsCentre lets you select either the centre or top left corner as the point of reference (CentreOfMass).
	//The Polygons worldspace coordinates can be specifyied with _Position. Defaulted to glm::vec3(0,0,0).
	//_AngleOffset indicates the rotation (around the Z axis) of the Polygon. Defaulted to 45 degrees.
	bool Create(int _Sides, glm::vec3 *_Verts, bool _CentreIsCentre, glm::vec3 _Position = glm::vec3(0.0f,0.0f,0.0f), float _AngleOffset = 45.0f);

	//Creates a Polygon with the specified _Verts.
	//Were _CentreIsCentre lets you select either the centre or top left corner as the point of reference (CentreOfMass).
	//The Polygons worldspace coordinates can be specifyied with _Position. Defaulted to glm::vec3(0,0,0).
	//_AngleOffset indicates the rotation (around the Z axis) of the Polygon. Defaulted to 45 degrees.
	bool Create(int _Sides, float *_Verts, bool _CentreIsCentre, glm::vec3 _Position = glm::vec3(0.0f,0.0f,0.0f), float _AngleOffset = 45.0f);
	
	bool Update();
	bool Draw(Shader _Shader);
	bool Move(glm::vec3 _Position);
	bool Rotate(float _Degrees);

private:
	unsigned int CalcIndices(int _Sides);//Works out what tris use what verts. thats what indices are you idiot.

	Vertex *CalcPoints(int _Sides, glm::vec3 _Centre, float _Radius, float _AngleOffset = 45.00f);//i think this should be 45.0f, else make it 90.0f; but it mainly only applies to quads
	Vertex *CalcPoints(int _Sides, glm::vec2 _Dimensions, glm::vec3 _Centre, float _AngleOffset = 45.00f);// params are rearranged to prevent confusion between the two if angle is not specified in this func

};

#endif