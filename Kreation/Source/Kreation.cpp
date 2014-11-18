#include "Kreator.h"

void main()
{

	WindowHandle.WinOpen(1024, 768, "Kreator - Test");

	//Tex = TextureHandle.Load(".//Kreation/Resources/TexturesPokedElliot.png", 30, 30);
	Sprite * Spr;
	Spr = new Sprite(4, 40, true, glm::vec3(0, 0, 0));

	while(WindowHandle.Winupdate(true))
	{
		
	}
	return;
}

