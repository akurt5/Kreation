#version 430

uniform vec4 inputColour;
out vec4 fragColour;

void main()
{
	//OutColour = vec4(0.0, 1.0, 0.0, 1.0);
	fragColour = inputColour;
}