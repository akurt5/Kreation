#include "LogHandle.h"
#include <ctime>
#include <iostream>

bool Logger::CreateLog()
{
	/*time_t RawTime;
	struct tm *TimeInfo;
	char Buffer[80];

	time (&RawTime);
	TimeInfo = localtime(&RawTime);

	strftime(Buffer, 80, "%d-%m-%Y %I:%M:%S", TimeInfo);
	std::string str(Buffer);
	str.append(".txt");
	Title = str.c_str();
	CreateLog(Title);*/
	return true;
}
bool Logger::CreateLog(const char *_LogName)
{
	//Log = fopen(_LogName, "w");
	return true;
}
bool Logger::LogError(int _Error, const char *_Description)
{
	//fputs(_Description, Log);
	return true;
}
bool Logger::CloseLog()
{
	//fclose(Log);
	return true;
}