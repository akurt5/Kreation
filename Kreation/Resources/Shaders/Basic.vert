#version 430

in vec3 In_Pos;

void main() 
{
	gl_Position = vec4(In_Pos, 1.0);
}