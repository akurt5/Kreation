#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "GL\glew.h"
class Attrib
{
public:
	Attrib(void *_Value, char *_Name );
	//template <typename AnyVal>
	void *Value; 
	char *Name;
	bool LockPos;
};

class ShaderUse
{
public:
	template <typename AnyVal>
	bool AddAttrib(AnyVal _Value, char *_Name );
	bool AddAttrib(Attrib _Att);
	template <typename AnyVal>
	bool AssignLocation(unsigned int _Location, AnyVal _Value, char *_Name);

	std::vector <Attrib>AttList;

};

class Shader
{
public:
	
	//Converts the loaded text file into a shader.
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
	
	//Takes an std::Vector supplied by the shader.
	//Vector holds all paths for shaders.
	//This function is used mainly for reloading shaders at runtime
	bool Load(std::vector<const GLchar *const *> _PathList);
	bool ReLoad();
	bool Update();
	bool SendAttribs();//maybe just pass a Charistic. they have a name already

	GLint VShader, CShader, EShader, GShader, FShader, ShaderProgram;

	//Enable use of Shader(class) as a variable 
	operator GLint() const {return ShaderProgram;}//When we try and use Shader(class) as a float is will return the program

	
	std::vector <const GLchar *const*>PathList;

	
	std::vector <Attrib>AttList;
	unsigned int Location;

	

};


#endif

