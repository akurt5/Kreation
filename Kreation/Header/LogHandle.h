#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <ctime>
#include <iostream>

#define KREATION_LOG "Kreation_LogFile.log"
#define KreationVN = "v0.25"

//each function should retunr something.
//and all debug logs should be stored in a vector of some sort.
//that way if a funtion ever returns something it shouldn't.
//the whole vector will be written to file named with the date and time.

namespace
{


	bool CreateLog(const char *_Message)
	{
		FILE *File;
		fopen_s(&File, KREATION_LOG, "w");
		if(!File)
		{
			fprintf(stderr, "ERROR: Could not open logfile %s for writing\n\n", KREATION_LOG);
			return false;
		}
		time_t now = time(NULL);
		char date[26]; 
		ctime_s(date, sizeof(date), &now);
		fprintf(File, _Message);
		fprintf(File, "\t\t\tKreation LogFile -Open for (busy)ness.\n\nLocal time %s\n\n", date);
		fclose(File);
		return true;
		}
	bool CreateLog()
	{
		CreateLog("Let's get cynical, cynical!\n");
		return true;
	}
	bool Log(const char *_Message, ...)
	{
		va_list Arg;
		FILE *File;
		fopen_s(&File, KREATION_LOG, "a");
		if(!File)
		{
			fprintf(stderr, "ERROR: Could not open logfile %s for Appending\n\n", KREATION_LOG);
			return false;
		}
		va_start(Arg, _Message);
		vfprintf(File, _Message, Arg);
		va_end(Arg);
		fclose(File);
		return true;
	}
	bool LogError(FILE *_File,const char *_Message, ...)
	{
		va_list Arg;
		
		fopen_s(&_File, KREATION_LOG, "a");//     Maybe don't need this, because i should be only calling it with "stderr" as a param
		if(!_File)
		{
			fprintf(stderr, "ERROR: Could not open logfile %s for Appending", KREATION_LOG);
			return false;
		}
		va_start(Arg, _Message);
		vfprintf(_File, _Message, Arg);
		vfprintf (stderr, _Message, Arg);//This line is the reason errors are outputting to console. besides it's probably kinda good if errors are up in my face and shit.
		va_end (Arg);
		fclose(_File);
		return true;
	}
	bool LogError(const char *_Message, ...)
	{
		FILE *File;
		fopen_s(&File, KREATION_LOG, "a");
		if(!File)
		{
			fprintf(stderr, "ERROR: Could not open logfile %s for Appending", KREATION_LOG);
			return false;
		}
		LogError(File, _Message);
	}
	
	bool SignLog(const char* _Message)
	{
		FILE *File;
		fopen_s(&File, KREATION_LOG, "a");
		if(!File)
		{
			fprintf(stderr, "ERROR: Could not open logfile %s for Appending\n\n", KREATION_LOG);
			return false;
		}
		time_t now = time(NULL);
		char date[26]; 
		ctime_s(date, sizeof(date), &now);
		fprintf(File, "\n\n\n\t\t\t\t\t\t\t   Kreation LogFile -Signing out.\n\n\t\t\t\t\t\t\t Local time %s\n\n", date);
		fprintf(File, _Message);
		fprintf(File, "\t\t\t\t/*---------------------------------------akurt5---------------------------------------*/\n\n");
		fclose(File);
		return true;
	}
	bool SignLog()
	{
		SignLog("\t\t\t\t\t\t\tLooking forward to hearing from you. :)\n\n\n");
		return true;
	}

	void GlfwErrorCallback(int _Error, const char *_Description)
	{
		LogError("GLFW ERROR: code %i msg: %s\n", _Error, _Description);
	}
};

#endif