#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "GL\glew.h"


class Shader
{
public:
	GLint CreateShader(const GLchar *const *_Path, GLenum _Type);
	GLint CreateProgram(GLint _Vert, GLint _Cont, GLint _Eval, GLint _Geom, GLint _Frag);
	//void Load(char *_ShaderPath, ...);
	bool Load(int _Count, ...);
	bool SendAttribs(...);

	GLint VShader, CShader, EShader, GShader, FShader, ShaderProgram;

	bool Load(std::vector<const char *> _PathList);
	std::vector <const char*>PathList;

};

#endif