#ifndef LOG_H
#define LOG_H

//each function should retunr something.
//and all debug logs should be stored in a vector of some sort.
//that way if a funtion ever returns something it shouldn't.
//the whole vector will be written to file named with the date and time.

class Logger
{
public:
	bool CreateLog();
	bool CreateLog(const char *_LogName);
	bool LogError(int _Error, const char *_Description);
	bool CloseLog();

	const char* Title;
	//FILE *Log;
};

#endif