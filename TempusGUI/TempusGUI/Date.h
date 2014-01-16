/*
Author: Ishaan Singal, Raunak Rajpuria
Date does the following:
--Contains information about a particular date (day, month, year), and stores all the events for that day (in a vector of Event objects -> eventList)
--Receives a call from the ListHandler to perform necessary functions on the vector of events
--Modifies the content of an Event object in the event vector based on the inputs from ListHandler
--Contains some helper functions used by itself, and other classes in the upper layer (to get the largest eventId for that day, compare two dates, increment dates etc)
*/
#ifndef _DATE_H
#define _DATE_H

#include "Event.h"
#include "TempusExceptions.h"
#include "TempusLibrary.h"

#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <ctime>

using namespace std;

class Date
{
public:
	Date();
	Date(int, int, int);

	int getDay();
	void setDay(int);

	int getMonth();
	void setMonth(int);

	int getYear();
	void setYear(int);

	Event getEvent(int);
	vector<Event> getEventList();

	int getEventListLength();
	bool isLeap();

	void addEvent(string id, string name, string location, Time, Time, string, string);
	void markEventAsDone(int markIndex);
	void Date::markEventAsNotDone(int markIndex);
	int dateDifference(Date);
	void deleteEvent(int);
	
	void editEventName(int editIndex, string name);
	void editEventLocation(int editIndex, string location);
	void editEventTime(int editIndex, Time startTime, Time endTime);
	void editEventTimeToDeadline(int editIndex, Time startTime, Time endTime);
	void incrementDays(int noOfDays);
	void decrementDays(int noOfDays);
	int getIndex(string);
	int compareDates(Date obj);
	string getLargestId();
	Date setDateObject(int day, int month, int year);

	Date dateStringToObject(string date);
	bool isValidDate(Date date);
	string getConvertedDate(string tempDate);
	
	~Date(void);
	
private:
	int day;
	int month;
	int year;
	vector<Event> eventList;
	
	int getCurrentDayIndex();
	vector<string> removeSlash(string date);
	bool hasSlashes(string date);
	int whichMonth(string month);
	bool isMonth(string month);
	int whichDay(string input);
	Date setDayToObject(int dayIndex);
	Date setTomorrowToObject();
	Date setDateWithSlashesToObject(string dateWithSlashes, Date currentDate);
	Date setDateIdToObject(string dateId);
	Date setDateWithMonthToObject(vector<string> tokenizedDate, Date currentDate);
	
};

#endif