#version 430

in vec3 InPos;

void main()
{
	gl_Position = vec4(InPos.x, InPos.y, InPos.z, 1.0);
}