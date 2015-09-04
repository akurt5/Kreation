#ifndef SHADER_H
#define SHADER_H

//#define BASIC_VERT = 
//#define BASIC_FRAG = 
//define basic shaders so Draw() on any object will include the most basic shader for that object.

#include <vector>

#include "GL\glew.h"

class ShaderControl /* DO I WANT THIS HERE????-->> I HAVE FORGOTTEN THE PURPOSE OF THIS CLASS. IT MAKES NO SENSE TO HAVE IT NOT INVOLVED IN SOME INHERITANCE	-->>	: public Shader*/
{
public:

	struct Uniform
	{
		unsigned int Location;
		const char *Name;
		GLenum DataType;
	};
	class UniformVec : public std::vector<Uniform>
	{
	public:
		typedef std::vector<Uniform> UniformVector;
		using UniformVector::size;

		Uniform& operator[](const char *_Name)
		{
			UniformVector &self = *this;
			if(size() > 0)
			{
				for(int i=0;i<size();i++)
				{
					if(!strcmp(self[i].Name, _Name)){return self[i];}
					else {printf("No uniform labeled %s is in the list.\nMaybe there is no list, maybe there is no you?\nAre we all just a dream? woah man.\n", _Name);}
				}
			}
			else
			{
				printf("Oooooh, nah, no Uniforms in this list mate, what are you gonna tell the missus..\n");
			} 
			Uniform Uni; return Uni;
		}
	};
	/*
	What is this class even for?? when would i want something to not have a shader but pretty much have one?

	Maybe shaders don't want to be able to create and send attributes to things.
	But ShaderUse is so anything (Shader or not can send and create attribs) (Y)

	SHould Shader then inherit from ShaderUse then??

	See Update function's description in Shader class for the epiphany in which i rediscovered the use for this class. 
	sometimes im an idiot. 
	when i created this class it was a stike if genoius.
	forgetting its purpose was all to typical of me
	however now that i have remembered its purpose(porpoise) nothing else matters
	*/

	UniformVec UniformList;

	//Compiles astd::vector of all active uniforms in the shader program.
	bool CompileUnifomVector(GLint _ShaderProgram);

	//Uniforms are variables passed into shaders.
	//This function scours your shaders until it finds this so called uniform's location.
	int GetUniformLocation(GLint _ShaderProgram, const char *_UniformName);// it's more than just a gletuniformlocation() wrapper. i think it should be only a wrapper for said function.

	//all variables are charistics .: they all hava a name .: gluniform function can get the list of charistics from the object and find "TexCoords" in that list.
	//variables need only be specified in shaders and existant in objs running the shader program.

	//bool AssignUniformValues(GLint _ShaderProgram, Uniform _Uniform, ...);//use va_args to get each param based on what data type is passed. 
	bool AssignUniformValues(GLint _ShaderProgram, const char *_UniformName, ...);//use va_args to get each param based on what data type is passed. 
};

class Shader// : public ShaderUse
{
public:
	
	//Converts the loaded text file into a shader.
	GLint CreateShader(const char *_ShaderFilePath, GLenum _Type);
	GLint CreateProgram(GLint _Vert, GLint _Cont, GLint _Eval, GLint _Geom, GLint _Frag);

	//Loads shader files of type:
	//.vert
	//.cont
	//.eval
	//.geom
	//.frag
	//
	//Just provide a file name for each.
	//e.g. Load(Basic.vert, Basic.frag);
	bool Load(int _Count, /*const GLchar *const **/char *_ShaderFileName, ...);
	
	//template <typename... T>
	//bool Load(T... _FileNames);
	
	
	
	//Takes an std::Vector supplied by the shader.
	//Vector holds all paths for shaders.
	//This function is used mainly for reloading shaders at runtime
	bool Load(std::vector<std::string> _PathList);

	//Uniforms are variables passed into shaders.
	//This function scours your shaders until it finds this so called uniform's location.
	//bool GetUniformLocation(const char *_UniformName);

	//Loads the contents of a shader file into a string via fstream
	//Used only in Load() to load shaders during initialisation
	//std::string GrabShaderSource(const char *_ShaderFilePath);

	//Calls Shader::Load(PathList);
	//PathList is a Vector containing all saved shader file paths
	//
	//Used to ReLoad all shader files at runtime.
	//e.g. if(KeyOnPress(KEY_R)){Shaders.ReLoad();}
	bool ReLoad();

	//Needs Work, atm Update just calls SendAttribs() which looks dangerous...
	//Might as well update in the draw func. 
	//seems way more senible.
	//						what draw func? just went looking and found none
	//maybe create one? 
	//						shaders don't get drawn though, they are called however. 
	//						can we detect that?
	//is this what the ShaderUse class is for?
	//						ill go check.. brb.
	//bool Update();

	//Looks Dangerous :S
	//bool SendAttribs();//maybe just pass a Charistic. they have a name already

	//Gets the shader log from GL then prints it to the log file.
	bool RetrieveShaderLog(GLuint _Shader);
	
	//Gets the program log from GL then prints it to the log file.
	bool RetrieveProgramLog(GLuint _Program);
	
	//Gets all sorts of bonus info from and about the shader program.
	//This function also calls RetrieveProgramLog(_Program)
	bool RetrieveAllProgramsLogs(GLuint _Program);

	GLint VShader, CShader, EShader, GShader, FShader, ShaderProgram;

	//Enable use of Shader(class) as a variable 
	operator GLint() const {return ShaderProgram;}//When we try and use Shader(class) as a float is will return the program

	//Holds All the paths for shaders that make up this Shader Program.
	//Primarily used in ReLoad()
	std::vector <std::string>PathList;

	
	//std::vector<Attrib>AttList;

	unsigned int Location;

private:
	//converts some gl types to strings for outbut in a logfile.
	const char *GlTypeToString(GLenum _Type);
	
	//bool Load(char *_ShaderName, ...);

};

#endif

