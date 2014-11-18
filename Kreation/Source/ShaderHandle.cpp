#include "ShaderHandle.h"
#include <sstream>
#include <stdarg.h>

template <typename AnyVal>
bool ShaderUse::AddAttrib(AnyVal _Value, char *_Name)
{
	Attrib Att = new Attrib(_Value, _Name);
	AttList.emplace_back(Att);
	return true;
}
bool ShaderUse::AddAttrib(Attrib _Att)
{
	AttList.emplace_back(_Att);
	return true;
}
template <typename AnyVal>
bool ShaderUse::AssignLocation(unsigned int _Location, AnyVal _Value, char *_Name)
{
	Attrib Att = new Attrib(_Value, _Name);
	Att.LockPos = true;
	Attrib ToBeMoved = AttList[_Location]
	if (ToBeMoved != Null)
	{
		if(ToBeMoved.LockPos != true)
		{
			AttList.emplace_back(ToBeMoved);
			AttList.erase(AttList.begin() + _Location);
			AttList.emplace(AttList.begin() + _Location, Att);
		}
		else 
		{
			printf("There is already an attribute locked to this position. please find another place for", _Name);
			return false;
		}
	}
	else
	{
		AttList.emplace(AttList.begin() + _Location, Att);
	}
	return true;
}
//--------------------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------------------//

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
//bool Shader::Load(int _Count, ...)
bool Shader::Load(const GLchar *const *_ShaderName, ...)//if were having trouble im not sure if this will work being a 'const GLchar *const *' maybe make it a char again. 
{
	const GLchar *const *a;
	va_list VariablePathList;
	va_start (VariablePathList, _ShaderName);
	//va_start (VariablePathList, _Count);
	
	
		VShader = 0;
		CShader = 0;
		EShader = 0;
		GShader = 0;
		FShader = 0;

	for(int i=0; i!=5; i++)//5 is the max amount of shaders that will make up our program
		{
		a = va_arg(VariablePathList, const GLchar *const *);
		if(a==NULL)//if this function is breaking. check this.
		{
			goto EndLoop;//i am anticipitaing that if nothing was passed for this particular argument than 'a' will be null. 
			//go to will skip ahead to the definition of EndLoop.
		}
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
		const GLchar *const *FullPath = (const GLchar *const *)sName.c_str();
		PathList.emplace_back(FullPath);
		printf((const char *)PathList[i]);printf("\n");//probably don't even want this line

	}
	EndLoop://goto will skip to here if there are no more shaders to get.
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
bool Shader::Load(std::vector<const GLchar *const *> _PathList)
{
	int Count = 0;
	const GLchar *const *Vert = nullptr, *const *Cont = nullptr, *const *Eval = nullptr, *const *Geom = nullptr, *const *Frag = nullptr;
	if(PathList[0]!= nullptr){Vert = PathList[0];}else{Count++;}
	if(PathList[1]!= nullptr){Cont = PathList[1];}else{Count++;}
	if(PathList[2]!= nullptr){Eval = PathList[2];}else{Count++;}
	if(PathList[3]!= nullptr){Geom = PathList[3];}else{Count++;}
	if(PathList[4]!= nullptr){Frag = PathList[4];}else if(Count == 4)
	{
		printf("Reloading shaders failed. no shaders were listed");
		return false;
	}//if count is 4 there must have been 4 fails prior to the final one.
	Load(Vert, Cont, Eval, Geom, Frag);
}
bool Shader::ReLoad()
{
	Load(PathList);
	return true;
}
bool Shader::Update()
{
	SendAttribs();
	return true;
}
bool Shader::SendAttribs()
{
	int Size = AttList.size();
	if(Size <= 0)
	{
		return false; // sending 0 things sounds dangerous.
	}

	for(Location=0;Location<Size;Location++)
	{
		glEnableVertexAttribArray(Location);
		//glBindAttribLocation(ShaderProgram, Location, "In_Colour");

	}
	return true;
}
//--------------------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------------------//

