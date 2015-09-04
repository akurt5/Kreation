#include "ShaderHandle.h"
#include "LogHandle.h"
#include "GLM/ext.hpp"

#include <sstream>
#include <stdarg.h>
#include <fstream>
#include <string>
/*Attrib::Attrib(void *_Value, char *_Name )
{
	Value = _Value;
	Name = _Name;
}
bool ShaderUse::AddAttrib(void *_Value, char *_Name)
{
	Attrib Att(_Value, _Name);
	AttList.emplace_back(Att);
	return true;
}
bool ShaderUse::AddAttrib(Attrib _Att)
{
	AttList.emplace_back(_Att);
	return true;
}
//template <typename AnyVal>
bool ShaderUse::AssignLocation(unsigned int _Location, void *_Value, char *_Name)
{
	Attrib Att(_Value, _Name);
	Att.LockPos = true;
	
	if (AttList.size() >= _Location)//(ToBeMoved != nullptr)
	{
		Attrib ToBeMoved = AttList[_Location];
		if(ToBeMoved.LockPos != true)
		{
			AttList.emplace_back(ToBeMoved);
			AttList.erase(AttList.begin() + _Location);
			AttList.emplace(AttList.begin() + _Location, Att);
		}
		else 
		{
			Log("There is already an attribute locked to this position. please find another place for", _Name);
			return false;
		}
	}
	else
	{
		AttList.emplace(AttList.begin() + _Location, Att);
	}
	return true;
}*/
bool ShaderControl::CompileUnifomVector(GLint _ShaderProgram)
{

	int UniformCount;
	glGetProgramiv(_ShaderProgram, GL_ACTIVE_UNIFORMS, &UniformCount);

	for(int i=0;i<UniformCount;i++)
	{
		
		int Size = 0;
		GLenum Type;
		GLchar Name[64];
		glGetActiveUniform (_ShaderProgram, i, NULL, NULL, &Size, &Type, Name);

		Uniform Uni;
		Uni.Name = (char*)Name;
		Uni.DataType = Type;
		Uni.Location = i;

		if (Size > 1) //if true then uniform must be an array of things.		actually passing an array could be cool. have the shader chooose things from your array as variables. 
		{//imagine an array of possible variables to use in a colour vec4(), array[0] is the colour then on cue randomly iterate through the array per fragment
			for (int j = 0; j < Size; j++)// I'm unsure if i want to have this much control here, it seems a bit much
			{
				char LongName[64];
				sprintf_s (LongName, "%s[%i]", Uni.Name, j);
				int Loc = glGetUniformLocation (_ShaderProgram, LongName);
				printf("the thing is happening and im not sure if you want it to. :)\n Ctrl+f the smiley to find this message and hopefully more info.\nAlso thing are definately not working properly here.\n\n");
			}
		} 
		else //if false the uniform is a single value. thats what we want right now yeah!? okay cool.
		{
			
			Uni.Location = glGetUniformLocation (_ShaderProgram, Uni.Name);
		}
		UniformList.emplace_back(Uni);
	}
	return true;
}
int ShaderControl::GetUniformLocation(GLint _ShaderProgram, const char *_UniformName)
{
	//Uniform Uni;
	//Uni.Name = _UniformName;
	//Uni.Location = glGetUniformLocation(_ShaderProgram, _UniformName);
	//UniformList.emplace_back(Uni);
	//return Uni.Location;//Uni;
	return glGetUniformLocation(_ShaderProgram, _UniformName);
}
/*bool ShaderControl::AssignUniformValues( GLint _ShaderProgram, Uniform _Uniform, ...)
{
	
}*/
bool ShaderControl::AssignUniformValues( GLint _ShaderProgram, const char *_UniformName, ...)
{
	int Size = 0;
	
	Uniform Uni;
	Uni = UniformList[_UniformName];

	glGetActiveUniform(_ShaderProgram, Uni.Location, NULL, NULL, &Size, &Uni.DataType, NULL);

	va_list ArgList;
	va_start(ArgList, _ShaderProgram);
	float r = (float)va_arg(ArgList, double);
	float g = (float)va_arg(ArgList, double);
	float b = (float)va_arg(ArgList, double);
	float a = (float)va_arg(ArgList, double);

	switch (Uni.DataType)
	{
		case(GL_FLOAT):				/*float			Arg = va_arg(ArgList, float);			*/	glUniform1f(Uni.Location, (float)va_arg(ArgList, double));	break;
		case(GL_FLOAT_VEC2):		/*float			Arg = va_arg(ArgList, glm::vec2);		*/	glUniform2f(Uni.Location, (float)va_arg(ArgList, double), (float)va_arg(ArgList, double));	break;
		case(GL_FLOAT_VEC3):		/*float			Arg = va_arg(ArgList, glm::vec3);		*/	glUniform3f(Uni.Location, (float)va_arg(ArgList, double), (float)va_arg(ArgList, double), (float)va_arg(ArgList, double));	break;
		case(GL_FLOAT_VEC4):		/*float			Arg = va_arg(ArgList, glm::vec4);		*/	glUniform4f(Uni.Location, r, g, b, a);	break;
		case(GL_DOUBLE):			/*double			Arg = va_arg(ArgList, double);		*/	glUniform1d(Uni.Location, va_arg(ArgList, double));	break;
		case(GL_DOUBLE_VEC2):		/*double			Arg = va_arg(ArgList, glm::dvec2);	*/	glUniform2d(Uni.Location, va_arg(ArgList, double), va_arg(ArgList, double));	break;
		case(GL_DOUBLE_VEC3):		/*double			Arg = va_arg(ArgList, glm::dvec3);	*/	glUniform3d(Uni.Location, va_arg(ArgList, double), va_arg(ArgList, double), va_arg(ArgList, double));	break;
		case(GL_DOUBLE_VEC4):		/*double			Arg = va_arg(ArgList, glm::dvec4);	*/	glUniform4d(Uni.Location, va_arg(ArgList, double), va_arg(ArgList, double), va_arg(ArgList, double), va_arg(ArgList, double));	break;
		case(GL_INT):				/*int				Arg = va_arg(ArgList, int);			*/	glUniform1i(Uni.Location, va_arg(ArgList, int));	break;
		case(GL_INT_VEC2):			/*int				Arg = va_arg(ArgList, glm::ivec2);	*/	glUniform2i(Uni.Location, va_arg(ArgList, int), va_arg(ArgList, int));	break;
		case(GL_INT_VEC3):			/*int				Arg = va_arg(ArgList, glm::ivec3);	*/	glUniform3i(Uni.Location, va_arg(ArgList, int), va_arg(ArgList, int), va_arg(ArgList, int));	break;
		case(GL_INT_VEC4):			/*int				Arg = va_arg(ArgList, glm::ivec4);	*/	glUniform4i(Uni.Location, va_arg(ArgList, int), va_arg(ArgList, int), va_arg(ArgList, int), va_arg(ArgList, int));	break;
		case(GL_UNSIGNED_INT):		/*unsigned int	Arg = va_arg(ArgList, unsigned int);	*/	glUniform1i(Uni.Location, va_arg(ArgList, unsigned int));	break;
		case(GL_UNSIGNED_INT_VEC2):	/*unsigned int	Arg = va_arg(ArgList, glm::uvec2);		*/	glUniform2i(Uni.Location, va_arg(ArgList, unsigned int), va_arg(ArgList, unsigned int));	break;
		case(GL_UNSIGNED_INT_VEC3):	/*unsigned int	Arg = va_arg(ArgList, glm::uvec3);		*/	glUniform3i(Uni.Location, va_arg(ArgList, unsigned int), va_arg(ArgList, unsigned int), va_arg(ArgList, unsigned int));	break;
		case(GL_UNSIGNED_INT_VEC4):	/*unsigned int	Arg = va_arg(ArgList, glm::uvec4);		*/	glUniform4i(Uni.Location, va_arg(ArgList, unsigned int), va_arg(ArgList, unsigned int), va_arg(ArgList, unsigned int), va_arg(ArgList, unsigned int));	break;
		case(GL_BOOL):				/*bool			Arg = va_arg(ArgList, bool);			*/	glUniform1i(Uni.Location, va_arg(ArgList, int));	break;
		case(GL_BOOL_VEC2):			/*bool			Arg = va_arg(ArgList, glm::bvec2);		*/	glUniform2i(Uni.Location, va_arg(ArgList, int), va_arg(ArgList, int));	break;
		case(GL_BOOL_VEC3):			/*bool			Arg = va_arg(ArgList, glm::bvec3);		*/	glUniform3i(Uni.Location, va_arg(ArgList, int), va_arg(ArgList, int), va_arg(ArgList, int));	break;
		case(GL_BOOL_VEC4):			/*bool			Arg = va_arg(ArgList, glm::bvec4);		*/	glUniform4i(Uni.Location, va_arg(ArgList, int), va_arg(ArgList, int), va_arg(ArgList, int), va_arg(ArgList, int));	break;
		/*case(GL_FLOAT_MAT2):		float			Arg = va_arg(ArgList, glm::mat2);			glUniformMatrix2fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT3):		float			Arg = va_arg(ArgList, glm::mat3);			glUniformMatrix3fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT4):		float			Arg = va_arg(ArgList, glm::mat4);			glUniformMatrix4fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT2x3):		float			Arg = va_arg(ArgList, glm::mat2x3);			glUniformMatrix2x3fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT2x4):		float			Arg = va_arg(ArgList, glm::mat2x4);			glUniformMatrix2x4fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT3x2):		float			Arg = va_arg(ArgList, glm::mat3x2);			glUniformMatrix3x2fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT3x4):		float			Arg = va_arg(ArgList, glm::mat3x4);			glUniformMatrix3x4fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT4x2):		float			Arg = va_arg(ArgList, glm::mat4x2);			glUniformMatrix4x2fv(Loc, Arg);	break;
		case(GL_FLOAT_MAT4x3):		float			Arg = va_arg(ArgList, glm::mat4x3);			glUniformMatrix4x3fv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT2):		double			Arg = va_arg(ArgList, glm::dmat2);			glUniformMatrix2dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT3):		double			Arg = va_arg(ArgList, glm::dmat3);			glUniformMatrix3dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT4):		double			Arg = va_arg(ArgList, glm::dmat4);			glUniformMatrix4dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT2x3):		double			Arg = va_arg(ArgList, glm::dmat2x3);		glUniformMatrix2x3dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT2x4):		double			Arg = va_arg(ArgList, glm::dmat2x4);		glUniformMatrix2x4dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT3x2):		double			Arg = va_arg(ArgList, glm::dmat3x2);		glUniformMatrix3x2dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT3x4):		double			Arg = va_arg(ArgList, glm::dmat3x4);		glUniformMatrix3x4dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT4x2):		double			Arg = va_arg(ArgList, glm::dmat4x2);		glUniformMatrix4x2dv(Loc, Arg);	break;
		case(GL_DOUBLE_MAT4x3):		double			Arg = va_arg(ArgList, glm::dmat4x3);		glUniformMatrix4x3dv(Loc, Arg);	break;
		case(GL_SAMPLER_1D):								printf("No data type for GL_SAMPLER_1D. YOU IDIOT.		p.s. pls fix this.");
		case(GL_SAMPLER_2D):								printf("No data type for GL_SAMPLER_2D. YOU IDIOT.		p.s. pls fix this.");
		case(GL_SAMPLER_3D):								printf("No data type for GL_SAMPLER_3D. YOU IDIOT.		p.s. pls fix this.");
		case(GL_SAMPLER_CUBE):								printf("No data type for GL_SAMPLER_CUBE. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_1D_SHADOW):							printf("No data type for GL_SAMPLER_1D_SHADOW. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_SHADOW):							printf("No data type for GL_SAMPLER_2D_SHADOW. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_1D_ARRAY):							printf("No data type for GL_SAMPLER_1D_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_ARRAY):							printf("No data type for GL_SAMPLER_2D_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_1D_ARRAY_SHADOW):					printf("No data type for GL_SAMPLER_1D_ARRAY_SHADOW. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_ARRAY_SHADOW):					printf("No data type for GL_SAMPLER_2D_ARRAY_SHADOW. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_MULTISAMPLE):printf("No data type for GL_SAMPLER_2D_MULTISAMPLE. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_MULTISAMPLE_ARRAY):printf("No data type for GL_SAMPLER_2D_MULTISAMPLE_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_CUBE_SHADOW):printf("No data type for GL_SAMPLER_CUBE_SHADOW. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_BUFFER):printf("No data type for GL_SAMPLER_BUFFER. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_RECT):printf("No data type for GL_SAMPLER_2D_RECT. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_SAMPLER_2D_RECT_SHADOW):printf("No data type for GL_SAMPLER_2D_RECT_SHADOW. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_1D):printf("No data type for GL_INT_SAMPLER_1D. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_2D):printf("No data type for GL_INT_SAMPLER_2D. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_3D):printf("No data type for GL_INT_SAMPLER_3D. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_CUBE):printf("No data type for GL_INT_SAMPLER_CUBE. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_1D_ARRAY):printf("No data type for GL_INT_SAMPLER_1D_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_2D_ARRAY):printf("No data type for GL_INT_SAMPLER_2D_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_2D_MULTISAMPLE):printf("No data type for GL_INT_SAMPLER_2D_MULTISAMPLE. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY):printf("No data type for GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_BUFFER):printf("No data type for GL_INT_SAMPLER_BUFFER. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_INT_SAMPLER_2D_RECT):printf("No data type for GL_INT_SAMPLER_2D_RECT. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_1D):printf("No data type for GL_UNSIGNED_INT_SAMPLER_1D. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_2D):printf("No data type for GL_UNSIGNED_INT_SAMPLER_2D. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_3D):printf("No data type for GL_UNSIGNED_INT_SAMPLER_3D. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_CUBE):printf("No data type for GL_UNSIGNED_INT_SAMPLER_CUBE. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_1D_ARRAY):printf("No data type for GL_UNSIGNED_INT_SAMPLER_1D_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_2D_ARRAY):printf("No data type for GL_UNSIGNED_INT_SAMPLER_2D_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE):printf("No data type for GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY):printf("No data type for GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_BUFFER):printf("No data type for GL_UNSIGNED_INT_SAMPLER_BUFFER. YOU IDIOT.		p.s. pls fix this.");break;
		case(GL_UNSIGNED_INT_SAMPLER_2D_RECT):printf("No data type for GL_UNSIGNED_INT_SAMPLER_2D_RECT. YOU IDIOT.		p.s. pls fix this.");break;*/
		default:printf("No Uniform thingy set up for this ahh... %s thing yet.", _UniformName);break;
	}
	return true;
}
//--------------------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------------------//

bool Shader::Load(int _Count, char *_ShaderFileName, ...)//if were having trouble im not sure if this will work being a 'const GLchar *const *' maybe make it a char again. 
{
	char *a;
	va_list VariablePathList;
	va_start (VariablePathList, _ShaderFileName);

	a = _ShaderFileName;

	
	VShader = 0;
	CShader = 0;
	EShader = 0;
	GShader = 0;
	FShader = 0;

	for(int i=0; i< _Count; i++)//5 is the max amount of shaders that will make up our program
	{
		std::string sName = a;
		
		std::string sType;
		//add the file type to sType
		sType.append(sName.end()-4, sName.end());//4 is because 'vert' is 4
		//all shaders equal 0
		//allows us to use only what we want
		
		

		std::stringstream ssPath;

		ssPath<<"./Shaders/"<<sName;
		sName = ssPath.str();

		const char *FullPath = sName.c_str();
		

		if(!sType.compare("vert")){

			VShader = CreateShader(FullPath, GL_VERTEX_SHADER);

		}else if(!sType.compare("frag")){
		
			FShader = CreateShader(FullPath, GL_FRAGMENT_SHADER);

		}else if(!sType.compare("cont")){

			CShader = CreateShader(FullPath, GL_TESS_CONTROL_SHADER);

		}else if(!sType.compare("eval")){

			EShader = CreateShader(FullPath, GL_TESS_EVALUATION_SHADER);

		}else if(!sType.compare("geom")){

			GShader = CreateShader(FullPath, GL_GEOMETRY_SHADER);

		}else{
			Log("Cannot define type of SHADER     %s\n\n", FullPath);
		}
		
		Log("Attempted to load a SHADER    %s\nIF there are NO SHADER ERRORS directly above this message, all is well.(shot)\n\n", FullPath);

		PathList.emplace_back(FullPath);//should i be adding the path or the shader source?
		

		a = va_arg(VariablePathList, char *);//this happens at the end because va_args skips the 1st param, and 'a' is init and set to 1st param before the for loop, so in other words it('a') comes in hot so we don't have to refuel till here.
		//}
	}
	va_end (VariablePathList);
		
	//const char* aszInputs[] =  { "Position", "Color", "Normal", "Tangent", "Binormal", "Indices", "Weights", "Texcoord1", "Texcoord2" };
	//const char* aszOutputs[] = { "outColour" };
	
	ShaderProgram = CreateProgram( VShader, CShader, EShader, GShader, FShader);

	// free our shader once we built our program
	glDeleteShader( VShader );
	glDeleteShader( CShader );
	glDeleteShader( EShader );
	glDeleteShader( GShader );
	glDeleteShader( FShader );
	return true;
}
bool Shader::Load(std::vector<std::string> _PathList)
{
	int Count = 0;
	const char *Vert = nullptr, *Cont = nullptr, *Eval = nullptr, *Geom = nullptr, *Frag = nullptr;
	if(&PathList[0]!= nullptr){Vert = PathList[0].c_str();}else{Count++;}
	if(&PathList[1]!= nullptr){Cont = PathList[1].c_str();}else{Count++;}
	if(&PathList[2]!= nullptr){Eval = PathList[2].c_str();}else{Count++;}
	if(&PathList[3]!= nullptr){Geom = PathList[3].c_str();}else{Count++;}
	if(&PathList[4]!= nullptr){Frag = PathList[4].c_str();}else if(Count == 4)
	{
		Log("Reloading shaders failed. no shaders were found in std::vector<>PathList");
		return false;
	}//if count is 4 there must have been 4 fails prior to the final one.
	Load(5, (char *)Vert, (char *)Cont, (char *)Eval, (char *)Geom, (char *)Frag);
}
GLint Shader::CreateShader(const char *_ShaderFilePath, GLenum _Type)// const GLchar *const * == a const reference to a const GLchar *
{
	GLuint OurShader = NULL;
	OurShader = glCreateShader (_Type);
	std::ifstream FileStream(_ShaderFilePath);
	std::string ShaderFileSourceData;
	ShaderFileSourceData.assign(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
	const char *FileSource = ShaderFileSourceData.c_str();
	glShaderSource (OurShader, 1, &FileSource, NULL);
	glCompileShader (OurShader);

	RetrieveShaderLog(OurShader);

	return OurShader;
}
GLint Shader::CreateProgram(GLint _Vert, GLint _Cont, GLint _Eval, GLint _Geom, GLint _Frag)
{
	ShaderProgram = glCreateProgram ();
	glAttachShader (ShaderProgram, _Vert);
	glAttachShader (ShaderProgram, _Cont);
	glAttachShader (ShaderProgram, _Eval);
	glAttachShader (ShaderProgram, _Geom);
	glAttachShader (ShaderProgram, _Frag);

	glLinkProgram (ShaderProgram);
	RetrieveAllProgramsLogs(ShaderProgram);

	return ShaderProgram;
}
bool Shader::ReLoad()
{
	Load(PathList);
	return true;
}
bool Shader::RetrieveShaderLog(GLuint _Shader)
{
	GLint Params = -1;
	glGetShaderiv(_Shader, GL_COMPILE_STATUS, &Params);
	if(GL_TRUE != Params)
	{
		LogError(stderr, "ERROR: GL Shader index %i did not compile\n", _Shader);
	}
	char Buffer[2048];
	glGetShaderInfoLog(_Shader, 2048, NULL, Buffer);
	Log(Buffer);
	return true;
}
bool Shader::RetrieveProgramLog(GLuint _Program)
{
	GLint Params = -1;
	glGetProgramiv(_Program, GL_LINK_STATUS, &Params);
	if(GL_TRUE != Params)
	{
		LogError(stderr, "Could not link shader programme GL index %u\n", _Program);
	}
	char Buffer[2048];
	glGetProgramInfoLog(_Program, 2048, NULL, Buffer);
	Log(Buffer);
	return true;
}
bool Shader::RetrieveAllProgramsLogs(GLuint _Program)
{
	Log("_________________________________________\nShader Program %i info\n", _Program);
	int Params = -1;
	glGetProgramiv(_Program, GL_LINK_STATUS, &Params);
	Log("GL_LINK_STATUS = %i\n", Params);

	glGetProgramiv(_Program, GL_ATTACHED_SHADERS, &Params);
	Log("GL_ATTACHED_SHADERS = %i\n", Params);

	glGetProgramiv(_Program, GL_ACTIVE_ATTRIBUTES, &Params);
	Log("GL_ACTIVE_ATTRIBUTES = %i\n", &Params);
	for(int i=0;i<Params;i++)
	{
		char Name[64];
		int MaxLength = 64;
		int ActualLength = 0;
		int Size = 0;
		GLenum Type;
		glGetActiveAttrib(_Program, i, MaxLength, &ActualLength, &Size, &Type, Name);
		if( Size > 1)
		{
			for(int j=0;j<Size;j++)
			{
				char LongName[64];
				sprintf_s(LongName, "%s[%i]", Name, j);
				int Loc = glGetAttribLocation(_Program, LongName);
				Log("	%i ) Type:%s Name:%s Location:%i\n", i, GlTypeToString(Type), LongName, Loc);
			}
		}
		else
		{
			int Loc = glGetAttribLocation(_Program, Name);
				Log("	%i ) Type:%s Name:%s Location:%i\n", i, GlTypeToString(Type), Name, Loc);
		}
	}

	glGetProgramiv(_Program, GL_ACTIVE_UNIFORMS, &Params);
	Log("GL_ACTIVE_UNIFORMS = %i\n", Params);
	for(int i=0;i<Params;i++)
	{
		char Name[64];
		int MaxLength = 64;
		int ActualLength = 0;
		int Size = 0;
		GLenum Type;
		glGetActiveUniform (_Program, i, MaxLength, &ActualLength, &Size, &Type, Name);

		if (Size > 1) 
		{
			for (int j = 0; j < Size; j++) 
			{
				char LongName[64];
				sprintf_s (LongName, "%s[%i]", Name, j);
				int Loc = glGetUniformLocation (_Program, LongName);
				Log("  %i) Type:%s Name:%s Location:%i\n", i, GlTypeToString(Type), LongName, Loc);
			}
		} 
		else 
		{
			int Loc = glGetUniformLocation (_Program, Name);
			Log("  %i) Type:%s Name:%s Location:%i\n", i, GlTypeToString(Type), Name, Loc);
		}
	}

	RetrieveProgramLog(_Program);
	return true;
}
const char *Shader::GlTypeToString(GLenum _Type)
{
	switch (_Type) {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }
  return "other";
}
//--------------------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------------------//