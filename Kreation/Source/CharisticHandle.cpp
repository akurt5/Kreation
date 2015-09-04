#include "CharisticHandle.h"
#include <typeinfo>

Charistic<class _Container>::Charistic(std::string *_Name, _Container *_DataType)
{
	Container = _DataType;
}

