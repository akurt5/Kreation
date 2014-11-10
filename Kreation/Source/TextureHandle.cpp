#include "TextureHandle.h"
//#include <Windows.h>


bool Texture::Load(char *_Path, int _Width, int _Height)//add wrapping enum (clamp, border, mirror, tile) also add filtering enum (nearest, linear, mipmaps and shit)
{
	glGenTextures(1, &Material);
	glBindTexture(GL_TEXTURE_2D, Material);
	Image = NULL;
	Image = SOIL_load_image(_Path, &_Width, &_Height, 0, SOIL_LOAD_RGBA);//get em boys
	if(!Image)
	{return false;}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _Width, _Height, 0, GL_RGBA, GL_FLOAT, Image);//give the image data to GL
	/*_______________________________________________________^_BorderSize_______________*/

	SOIL_free_image_data(Image);//frees up memory occupied when loading texture.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// s,t&r coords are  x,y&z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//Set image border colour.
	//float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	//Set filter options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Minifying //Specifies which kind of interpolation to use when scaling.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Magnifying // GL_LINEAR is the interpolation.
	

	//float pixels[] = {
	//	0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	//};
	//Pixels = pixels;

	

	//Generate MipMaps // Load Texture first
	//glGenerateMipmap(GL_TEXTURE_2D);
	return true;
}
bool Texture::Update(Shader _ShaderProgram)
{
	
	return true;
}
bool Texture::Move(glm::vec3 _Pos)
{
		
	return true;
}
bool Texture::Rotate(float _Angle)
{
		
	return true;
}
bool Texture::Draw()
{
		
	return true;
}