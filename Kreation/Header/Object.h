#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "CharisticHandle.h"

class Object
//										Objects are everything. Just add more Characteristics
{
public:
	enum Passes
	{
		DIE, //Destroy current and give all Charistics
		MENTOR, //Give Charistics and values
		RETIRE //Give Charistics but not values
	};

	Object();
	Object(Charistic, ...);//				va_args for Dynamics. #yeaboi!
	~Object();
	void PassOn( Passes _WayToGo, Object *_Successor, ...);//		Pass on then ~Object()
	
	void AddCharistic(Charistic, ...);

	inline Charistic* operator[](char *_Name);
	

	std::vector<Charistic*> Charistics;//Taste hold love the Charistics..
	//					Maybe make a custom list to hold these 
	//					if sort / find is too dificult
};
#endif