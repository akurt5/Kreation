#include "Kreator.h"
#include <cstdlib>//only for system("pause");

void main()
{
	Kreator *Application = new Kreator();
	//system("pause");
	while(Application->WinCheckClose())//check close should be called in a window update after close flags / hints have been set. such hints should be set via key presses and such
	{

	}
	Application->~Kreator();
	return;
}

