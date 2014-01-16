/*
Authors : Winnie Har
Event does the following:
--Contains all the information about each event (name, time, location etc)
--Contains two Time objects, startTime and endTime
*/
#ifndef _EVENT_H
#define _EVENT_H

#include <iostream>
#include <string>
#include <ctype.h>
#include "Time.h"
using namespace std;

class Event
{
public:
	Event();
	Event(string id, string name, string location, Time, Time, string, string);
	
	string getId ();
	void setId(string);

	string getName();
	void setName(string);

	Time getStartTime();
	void setStartTime(Time);

	Time getEndTime();
	void setEndTime(Time);

	string getLocation();
	void setLocation(string);

	string getEventType();
	void setEventType(string);

	string getEventStatus();
	void setEventStatus(string);

	string getEventDetails ();
	~Event(void);

private:
	string id;
	string name;
	string location;
	string eventType;
	string eventStatus;
	Time startTime;
	Time endTime;

	string formatDisplay(string);
};

#endif