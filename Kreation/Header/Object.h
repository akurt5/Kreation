#ifndef OBJECT_H
#define OBJECT_H

#include<string>
#include <map>

#include "CharisticHandle.h"

class Object : public Charistic<class _Container>
//										Objects are everything. Just add more Characteristics
{
public:

	enum Passes//gaaaaaaaaaaaaaaaaaaaaaaaaaaaaay, wot faggit thort thiz waz goodz ideer? faggit bitch. gay homo.
	{
		EXPIRE, //Destroy current and give all Charistics
		MENTOR, //Give Charistics and values
		RETIRE, //Give Charistics but not values
		INCITE  //Give values of mutual Charistics
	};

	Object();
	Object(Charistic<class _Container>, ...);//				va_args for Dynamics. #yeaboi!
	~Object();
	bool PassOn( Passes _Method, Object *_Successor, ...);//		Pass on then ~Object()
	
	//bool AddCharistic(Charistic<class _Container>, ...);
	bool AddCharistic(const char * _Name, Charistic<class _Container> _Charistic);

	//std::map<std::string *, Charistic<class _Container>*> Charistics;//Taste hold love the Charistics..
	template<typename DataType>
	std::map<std::string *, DataType>> Charistics;//Taste hold love the Charistics..
	template<typename DataType>
	bool AddCharistic(const char * _Name, DataType);

};
#endif