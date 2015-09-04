#include "Kreator.h"

bool main()
{
	Window::WinOpen("Kreation - Test");//, 1024, 768);

	Shader BasicShader;
	BasicShader.Load(2, "Basic.vert", "Basic.frag");
	
	Poly Pol;
	//Pol.Create(THREE, 1.00f, true, glm::vec3(0,0,0), 0.000f);
	float Verts[] = {0, 0.5f, 0, 
					0.5f, -0.5f, 0, 
					-0.5f, -0.5f, 0};
	Pol.Create(THREE, Verts, true);
	
	//Pol.GetUniformLocation(BasicShader, "InColour");
	while(Window::WinUpdate(true))
	{
		Pol.Draw(BasicShader);
		Pol.AssignUniformValues(BasicShader, "inputColour", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		//glUniform4f(Pol.GetUniformLocation(BasicShader, "inputColour"), 0.0f, 1.0f, 0.0f, 1.0f);
	}
	return true;
}

