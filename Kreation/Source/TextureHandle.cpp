#include "TextureHandle.h"
#include "LogHandle.h"
#include <stdio.h>
#include <sstream>

bool Tex::Load(char *_Path, int _Width, int _Height)//add wrapping enum (clamp, border, mirror, tile) also add filtering enum (nearest, linear, mipmaps and shit)
{
	
	Material = 0;//NULL
			//Image = SOIL_load_image(_Path, &_Width, &_Height, 0, SOIL_LOAD_RGBA);//get em boys
	Material = SOIL_load_OGL_texture(_Path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, 0);
	if(!Material)
	{
		Log("A Texture could not be loaded for reasons unknown. It is located at.. '%s'\n", _Path);	
		Log( "SOIL loading error: '%s'\n'\n", SOIL_last_result() );
		return false;
	}
	Log("\n' Loaded an image i guess '%s'\n", _Path);
	Log( "SOIL loading error: '%s'\n'\n", SOIL_last_result() );

	glGenTextures(1, &Material);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Material);
		  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _Width, _Height, 0, GL_RGBA, GL_FLOAT, Image);//give the image data to GL
	/*_______________________________________________________^_BorderSize_______________*/

			//SOIL_free_image_data(Image);//frees up memory occupied when loading texture.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// s,t&r coords are  x,y&z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//Set image border colour.
	//float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	//Set filter options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Minifying //Specifies which kind of interpolation to use when scaling.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//Magnifying // GL_NEAREST is the interpolation.
	

	//Generate MipMaps // Load Texture first
	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);//Bind it to nothing -clear it.


	//delete[] Image;//Clear the lingering pixel data.
	return true;
}