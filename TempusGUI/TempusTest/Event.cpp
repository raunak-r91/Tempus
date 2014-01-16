/*
Authors : Winnie Har
Event does the following:
--Contains all the information about each event (name, time, location etc)
--Contains two Time objects, startTime and endTime
*/
#include "Event.h"


Event::Event()
	: id (""), name(""), location (""), eventType(""), eventStatus("")
{
}


Event:: Event (string id, string name, string location, Time startTime, Time endTime, string eventType, string eventStatus)
	: id (id), name(name), location (location), startTime (startTime), endTime (endTime), eventType(eventType), eventStatus(eventStatus)
{
}

string Event:: getId ()
{
	return id;
}

void Event:: setId(string id)
{
	this->id =id;
}

string Event:: getName()
{
	return name;
}

void Event::setName(string name)
{
	this->name =name ;
}


Time Event:: getStartTime()
{
	return startTime;
}

void Event::setStartTime(Time time)
{
	this->startTime =time;
}

Time Event:: getEndTime()
{
	return endTime;
}

void Event::setEndTime(Time time)
{
	this->endTime =time;
}

string Event::getLocation()
{
	return location;
}

void Event::setLocation(string location)
{
	this->location = location;
}

string Event::getEventType()
{
	return eventType;
}

void Event::setEventType(string type)
{
	eventType = type;
}
	
string Event::getEventStatus()
{
	return eventStatus;
}

void Event::setEventStatus(string status)
{
	eventStatus = status;
}

string Event::getEventDetails ()
{
	stringstream output;
	if (getEventType()!="d")
		output << getStartTime().formatCompleteTime(getEndTime()) << " - ";
	 
	output << formatDisplay(getName()) ;
	if (getLocation()!="")
		output << " at "<< formatDisplay(getLocation());
	if (getEventType()=="d")
		output << " (by " << getStartTime().formatCompleteTime(getEndTime()) << ")";
	output<<" " << getEventStatus();
	output << endl;

	return output.str();

}
string Event::formatDisplay(string text)
{
	string formattedText="";
	if(text.size()!=0)
	{
		formattedText=(char)toupper(text[0]);
		formattedText+=text.substr(1);
	}
	return formattedText;
}

Event::~Event(void)
{
}