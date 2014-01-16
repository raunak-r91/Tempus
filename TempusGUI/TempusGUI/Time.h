/*
Authors : Winnie Har
Time does the following:
--Contains all the information about a specific time (hour, minutes, am/pm)
--Contains certain helper functions used by other classes in the upper layer(such as to format the time, get the time in a string form, check whether one time is greater than the other, increment time)
*/
#ifndef _TIME_H
#define _TIME_H

#include <string>
#include <sstream>
#include <vector>
#include "TempusExceptions.h"
#include "TempusLibrary.h"

#include <cassert>

using namespace std;

class Time
{
public:
	Time(void);
	Time(int, int,string);

	~Time(void);

	int getHour();
	int getMinutes();
	void setHour(int);
	void setMinutes(int);
	string getAmPm();
	void setAmPm(string);
	bool isGreaterThan(Time);
	//bool getStartEndTime(string timeString, Time time[]);
	string formatTime();

	void timeStringToObject(string timeString);
	bool isValidTime();
	string formatCompleteTime(Time timeObj);
	void incrementTime(int mins);
	bool isTimeEqual(Time timeObj);

private:
	int hour;
	int minutes;
	string am_pm;

	int findAmPm(string timeToBeTested);
	int findHyphen(string timeToBeTested);
	int hasAmPm(vector<string> tokenizedTime);
	vector<string> tokenizeTime(string timeToTokenize);


};

#endif