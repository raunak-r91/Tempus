/*
Author: Ishaan Singal, Raunak Rajpuria
Date does the following:
--Contains information about a particular date (day, month, year), and stores all the events for that day (in a vector of Event objects -> eventList)
--Receives a call from the ListHandler to perform necessary functions on the vector of events
--Modifies the content of an Event object in the event vector based on the inputs from ListHandler
--Contains some helper functions used by itself, and other classes in the upper layer (to get the largest eventId for that day, compare two dates, increment dates etc)
*/
#include "stdafx.h"
#include "Date.h"


Date::Date()
{
	day = 0;
	month = 0;
	year=0;
}

Date::Date(int day, int month, int year)
{
	day = day;
	month = month;
	year=year;
}

int Date::getDay()
{
	return day;
}
void Date::setDay(int day)
{
	this->day=day;
}
int Date::getMonth()
{
	return month;
}
void Date::setMonth(int month)
{
	this->month=month;
}
int Date::getYear()
{
	return year;
}
void Date::setYear(int year)
{
	this->year=year;
}
Event Date::getEvent(int eventIndex )
{
	return eventList[eventIndex];
}
int Date::getEventListLength()
{
	return eventList.size();
}

vector<Event> Date::getEventList()
{
	return eventList;
}
int Date::compareDates(Date obj)
{
	int date1,date2;
	date1=year*10000+month*100+day;
	date2=obj.year*10000+obj.month*100+obj.day;
	return date2-date1;
}
int Date::dateDifference(Date dateToCompare)
{
	Date temp;
	temp.setDay(getDay());
	temp.setMonth(getMonth());
	temp.setYear(getYear());
	
	int difference=0;
	if(temp.compareDates(dateToCompare)>=0)
	{
		while(temp.compareDates(dateToCompare)!=0)
		{
			temp.incrementDays(1);
			difference++;
		}
	}
	else
	{
		while(dateToCompare.compareDates(temp)!=0)
		{
			dateToCompare.incrementDays(1);
			difference++;
		}
	}

	return difference;
}
void Date::addEvent(string id, string name, string location, Time startTime, Time endTime, string eventType, string eventStatus)
{
	int i=0;
	Event currentObject (id,name, location, startTime, endTime, eventType, eventStatus);
	for(i=0;i<eventList.size();i++)
	{
		if(currentObject.getStartTime().isGreaterThan(eventList[i].getStartTime()))
			continue;
		else break;
	}
	eventList.insert(eventList.begin()+i,currentObject);
	return;
}

void Date::deleteEvent(int deleteIndex)
{
	vector<Event>::iterator it;
	it = eventList.begin()+deleteIndex;
	eventList.erase(it);
	vector<Event>(eventList).swap(eventList);
}

void Date::editEventName(int editIndex, string name)
{
	eventList[editIndex].setName(name);
}

void Date::editEventLocation(int editIndex, string location)
{
	eventList[editIndex].setLocation(location);
}

void Date::editEventTime(int editIndex, Time startTime, Time endTime)
{
	eventList[editIndex].setStartTime(startTime);
	eventList[editIndex].setEndTime(endTime);
	Event tempObj=eventList[editIndex];
	deleteEvent(editIndex);
	addEvent(tempObj.getId(),tempObj.getName(),tempObj.getLocation(),tempObj.getStartTime(),tempObj.getEndTime(), tempObj.getEventType(), tempObj.getEventStatus());
}

void Date::editEventTimeToDeadline(int editIndex, Time startTime, Time endTime)
{
	eventList[editIndex].setStartTime(startTime);
	eventList[editIndex].setEndTime(endTime);
	eventList[editIndex].setEventType("d");
	Event tempObj=eventList[editIndex];
	deleteEvent(editIndex);
	addEvent(tempObj.getId(),tempObj.getName(),tempObj.getLocation(),tempObj.getStartTime(),tempObj.getEndTime(), tempObj.getEventType(), tempObj.getEventStatus());
}

int Date::getIndex(string givenId)
{
	for (int i=0; i <eventList.size(); i++)
	{
		if (givenId==eventList[i].getId())
			return i;
	}
	return -1;
}
void Date::incrementDays(int noOfDays)
{
	int daysInMonths[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(isLeap())
		daysInMonths[2]+=1;
	for(int i=1;i<=noOfDays;i++)
	{
		day++;
		if(day > daysInMonths[month])
		{
			month++;
			if(month > 12)
			{
				year++;
				if(isLeap())
					daysInMonths[2]+=1;
				month=1;
			}
			day=1;
		}
	}
}

void Date::decrementDays(int noOfDays)
{
	int daysInMonths[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(isLeap())
		daysInMonths[2]+=1;
	for(int i=1;i<=noOfDays;i++)
	{
		day--;
		if(day <= 0)
		{
			month--;
			if(month < 1)
			{
				year--;
				if(isLeap())
					daysInMonths[2]+=1;
				month=12;
			}
			day=daysInMonths[month];
		}
	}
}
bool Date::isLeap()
{
	if( year % 4==0 && year%100 !=0 || year % 400 ==0)
		return  true;
	return false;
}
string Date::getLargestId()
{
	string currentId = "", prevId = "";

	for (int i =0; i <getEventListLength(); i++)
	{
		currentId = getEvent(i).getId();
		if (currentId > prevId)
			prevId = currentId;
	}
	return prevId;
}


vector<string> Date::removeSlash(string date)
{
	vector<string> dateWithoutSlash;
	char *pch;
	char *str;
	str = new char [date.size()+1];
	strcpy(str, date.c_str());

	pch = strtok(str,"/.");
	while(pch!=NULL)
	{
		dateWithoutSlash.push_back(pch);
		pch=strtok(NULL,"/.");
	}
	return dateWithoutSlash;
}
bool Date::hasSlashes(string date)
{
	int pos=date.find('/');
	int pos2=date.find('.');
	if(pos>-1 || pos2>-1)
		return true;
	return false;
}
Date Date:: setDateObject(int day, int month, int year)
{
	
	Date dateObjectToBeReturned;
	dateObjectToBeReturned.setDay(day);
	dateObjectToBeReturned.setMonth(month);
	dateObjectToBeReturned.setYear(year);
	return dateObjectToBeReturned;
}
int Date::whichMonth(string month)
{
	string months[]={"january","february","march","april","may","june","july","august","september","october","november","december"};
	month=toLower(month);
	int i;
	for(i=0;i<12;i++)
	{
		if(months[i].compare(0,month.size(),month)==0)
			break;
	}
		
	return i+1;
}
bool Date::isMonth(string month)
{
	string months[]={"january","february","march","april","may","june","july","august","september","october","november","december"};
	month=toLower(month);
	bool flag=false;

	if(month.size()>=3)
	{
		for(int i=0;i<12;i++)
		{
			if(months[i].compare(0,month.size(),month)==0)
			{
				flag=true;
				break;
			}
		}
	}
	return flag;
}
bool Date::isValidDate(Date date)
{
	bool flag=true;
	if(date.getDay()<1)
		flag=false;
	if(date.getMonth()<1 || date.getMonth()> 12)
		flag=false;
	if(date.getYear()<2011 || date.getYear() > 2099)
		flag=false;
	int daysInMonths[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(date.isLeap())
		daysInMonths[2]+=1;
	if(date.getDay()>daysInMonths[date.getMonth()])
		flag=false;
	return flag;
}

int Date::getCurrentDayIndex()
{
	time_t t=time(0);
	tm* now=localtime(&t);
	return now->tm_wday;
}

int Date::whichDay(string input)
{
	string days[]={"sunday" , "monday","tuesday", "wednesday", "thursday", "friday", "saturday"};
	for(int i=0;i<7;i++)
	{
		if(equalsIgnoreCase(input, days[i]))
			return i;
	}
	return -1;
}

Date Date::setDayToObject(int dayIndex)
{
	int currentDay = getCurrentDayIndex();
	Date newDate=*this;
	if (currentDay==dayIndex);
							
	else if (currentDay < dayIndex)
		newDate.incrementDays(dayIndex-currentDay);
	
	else 
		newDate.incrementDays(7+dayIndex-currentDay);
	
	return newDate;
}

Date Date::setTomorrowToObject()
{
	Date newDate;
	newDate=*this;
	newDate.incrementDays(1);
	return newDate;
}

Date Date::setDateWithSlashesToObject(string dateWithSlashes, Date currentDate)
{
	int day=0, month=0, year=0;
	vector<string> dateWithoutSlash= removeSlash(dateWithSlashes);
	day = atoi(dateWithoutSlash[0].c_str());
	month = atoi(dateWithoutSlash[1].c_str());

	if(dateWithoutSlash.size()==2)
	{
		year = this->getYear();
		Date tempDate=setDateObject(day, month, year);
		if(tempDate.compareDates(currentDate) >0)
			year+=1;
	}
		
	
	else if(dateWithoutSlash.size()==3)
		year= atoi(dateWithoutSlash[2].c_str());
	
	Date newDate=setDateObject(day,month,year);
	return newDate;
}

Date Date::setDateIdToObject(string dateId)
{
	int day=atoi(dateId.substr(0,2).c_str());
	int month=atoi(dateId.substr(2,2).c_str());
	int year= atoi(dateId.substr(4,4).c_str());

	Date newDate=setDateObject(day,month,year);
	return newDate;
}

Date Date::setDateWithMonthToObject(vector<string> tokenizedDate, Date currentDate)
{
	int day=0, month=0, year=0;
	if(isMonth(tokenizedDate[0]))
	{
		day=atoi(tokenizedDate[1].c_str());
		month=whichMonth(tokenizedDate[0]);
		year = this->getYear();
	}

	else if(isMonth(tokenizedDate[1]))
	{
		day=atoi(tokenizedDate[0].c_str());
		month=whichMonth(tokenizedDate[1]);
		year = this->getYear();
	}

	if (tokenizedDate.size()==2)
	{
		Date tempDate=setDateObject(day, month, year);
		if(tempDate.compareDates(currentDate) >0)
			year+=1;
	}
	if (tokenizedDate.size()==3)
		year=atoi(tokenizedDate[2].c_str());

	Date newDate=setDateObject(day, month, year);
	return newDate;
}

Date Date::dateStringToObject(string date)
{
	Date convertedDateObject;
	vector <string> tokenizedDate=tokenize(date);
	int dayIndex=-1;
		
	if(tokenizedDate.size()==1)
	{
		dayIndex=whichDay(date);
		if (dayIndex!=-1)
			convertedDateObject=setDayToObject(dayIndex);
				
		else if(equalsIgnoreCase(date, "today"))
			convertedDateObject=*this;
			
		else if(equalsIgnoreCase(date, "tomorrow"))
			convertedDateObject=setTomorrowToObject();
			
		else if (hasSlashes(date))
			convertedDateObject=setDateWithSlashesToObject(date, *this);

		else if (date.size()==8)
			convertedDateObject=setDateIdToObject(date);
			
	}

	else if(tokenizedDate.size()>1 && tokenizedDate.size()<4)
		convertedDateObject=setDateWithMonthToObject(tokenizedDate, *this);
		
	return convertedDateObject;
}



string Date::getConvertedDate(string tempDate)
{
	assert(tempDate!="");
	stringstream convertedDate ("");
	int day = atoi(tempDate.substr(0,2).c_str());//(tempDate.substr(0,2));
	int month = atoi (tempDate.substr(2,2).c_str());
	int year = atoi(tempDate.substr(4,4).c_str());
	
	convertedDate<<day;
	if (day%10==1 && day!=11)
		convertedDate<<"st ";
	else if (day%10==2 && day!=12)
		convertedDate<<"nd ";
	else if (day%10==3 && day!=13)
		convertedDate<<"rd ";
	else 
		convertedDate<<"th ";

	string months[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	convertedDate<<months[month-1];
	convertedDate<<", ";
	convertedDate<<year;

	return convertedDate.str();
}

void Date::markEventAsDone(int markIndex)
{
	eventList[markIndex].setEventStatus("d");
}

void Date::markEventAsNotDone(int markIndex)
{
	eventList[markIndex].setEventStatus("nd");
}

Date::~Date(void)
{
}


