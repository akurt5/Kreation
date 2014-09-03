#include "Object.h"


inline Charistic* Object::operator[](char *_Name)
{
	for (auto i : Charistics)
	{
		if(i->Name == _Name)
			return i;
	}
}