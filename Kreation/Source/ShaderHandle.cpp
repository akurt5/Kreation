#include "ShaderHandle.h"
#include <sstream>
#include <stdarg.h>

GLint Shader::CreateShader(const GLchar *const *_Path, GLenum _Type)
{
	GLuint Shader = NULL;
	Shader = glCreateShader (_Type);
	glShaderSource (Shader, 1, _Path, NULL);
	glCompileShader (Shader);
	return Shader;
}
GLint Shader::CreateProgram(GLint _Vert, GLint _Cont, GLint _Eval, GLint _Geom, GLint _Frag)
{
	ShaderProgram = NULL;
	ShaderProgram = glCreateProgram ();
	glAttachShader (ShaderProgram, _Vert);
	glAttachShader (ShaderProgram, _Cont);
	glAttachShader (ShaderProgram, _Eval);
	glAttachShader (ShaderProgram, _Geom);
	glAttachShader (ShaderProgram, _Frag);
	glLinkProgram (ShaderProgram);
	return ShaderProgram;
}
bool Shader::Load(int _Count, ...)
//bool Shader::Load(char *_ShaderName, ...)
{
	const GLchar *const *a;
	va_list VariablePathList;
	//va_start (VariablePathList, _ShaderName);
	va_start (VariablePathList, _Count);
	
	
		VShader = 0;
		CShader = 0;
		EShader = 0;
		GShader = 0;
		FShader = 0;

	for(int i=0; i!=_Count; i++)
		//for(bool i=true;i==true;i=false)
		{
		//a = NULL;
		a = va_arg(VariablePathList, const GLchar *const *);
		//if(a != 0){i = true;}
		std::string sName((char *)a);
		
		std::string sType;
		//add the file type to sType
		sType.append(sName.end()-4, sName.end());//4 is because 'vert' is 4
		//all shaders equal 0
		//allows us to use only what we want
		
		
		std::stringstream ssPath;

		ssPath<<"/Kreation/Resources/Shaders"<<sName;
		sName = ssPath.str();

			//switch to identify shader type
			  if(!sType.compare("vert")){

			VShader = CreateShader((const GLchar *const *)sName.c_str(), GL_VERTEX_SHADER);

		}else if(!sType.compare("cont")){

			CShader = CreateShader((const GLchar *const *)sName.c_str(), GL_TESS_CONTROL_SHADER);

		}else if(!sType.compare("eval")){

			EShader = CreateShader((const GLchar *const *)sName.c_str(), GL_TESS_EVALUATION_SHADER);

		}else if(!sType.compare("geom")){

			GShader = CreateShader((const GLchar *const *)sName.c_str(), GL_GEOMETRY_SHADER);

		}else if(!sType.compare("frag")){
			
			FShader = CreateShader((const GLchar *const *)sName.c_str(), GL_FRAGMENT_SHADER);

		}else{
			printf("Cannot define type of shader     ", sName.c_str(), '\n');
		}
		const char* FullPath = sName.c_str();
		PathList.emplace_back(FullPath);
		printf(PathList[i]);printf("\n");

	}
	va_end (VariablePathList);
		
	const char* aszInputs[] =  { "Position", "Color", "Normal", "Tangent", "Binormal", "Indices", "Weights", "Texcoord1", "Texcoord2" };
	const char* aszOutputs[] = { "outColour" };
	
	ShaderProgram = CreateProgram( VShader, CShader, EShader, GShader, FShader);

	// free our shader once we built our program
	glDeleteShader( VShader );
	glDeleteShader( CShader );
	glDeleteShader( EShader );
	glDeleteShader( GShader );
	glDeleteShader( FShader );
	return true;
}
bool Shader::SendAttribs(...)
{
	return true;
}
