#version 430

uniform vec4 In_Colour; //the uniform keyword says the attrib is comming from the cpu and not the gpu like usual. this also makes it global
out vec4 Out_Colour;

void main() 
{
	OUT_Colour = In_Colour;
}