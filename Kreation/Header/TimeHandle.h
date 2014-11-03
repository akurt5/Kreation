#ifndef TIME_H_
#define TIME_H_

class Time
{
public:
	double CurrentTime, Delta;

	double GetTime();
	bool Update();

};

#endif