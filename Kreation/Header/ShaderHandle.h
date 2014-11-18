#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "GL\glew.h"

class Shader
{
public:
	GLint CreateShader(const GLchar *const *_Path, GLenum _Type);
	GLint CreateProgram(GLint _Vert, GLint _Cont, GLint _Eval, GLint _Geom, GLint _Frag);
	//Loads shader files of type:
	//.vert
	//.cont
	//.eval
	//.geom
	//.frag
	//
	//Just provide a file name for each.
	//e.g. Load(Simple.vert, Simple.frag);
	bool Load(const GLchar *const *_ShaderName, ...);
	bool Update();
	bool SendAttribs();//maybe just pass a Charistic. they have a name already
	template <typename AnyVal>
	bool AddAttrib(AnyVal _Value, char *_Name );
	template <typename AnyVal>
	bool AssignLocation(unsigned int _Location, AnyVal _Value, char *_Name);

	GLint VShader, CShader, EShader, GShader, FShader, ShaderProgram;

	//bool Load(std::vector<const char *> _PathList); I dont know what this does..???
	std::vector <const char*>PathList;
	
	std::vector <Attrib>AttList;
	unsigned int Location;

	

};

class Attrib
{
public:
	Attrib(void *_Value, char *_Name );
	void *Value; 
	char *Name;
	bool LockPos;
};
#endif