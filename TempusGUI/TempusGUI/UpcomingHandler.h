/*
Authors : Ishaan Singal, Raunak Rajpuria
UpcomingHandler does the following:  
--Subclasses of ListHandler class. It handles upcoming events. 
--It is a singleton class. Only one instance of this class can be created.
--Apart from inheriting the attributes and methods of the parent class, it has certain methods of its own to act on its type of list (i.e Upcoming).
*/
#pragma once

#include "ListHandler.h"


using namespace std;

class UpcomingHandler : public ListHandler 
{

public:
	
	~UpcomingHandler(void);
	static UpcomingHandler* getInstance();
	void addEvent(CommandParser&);
	void editEvent(CommandParser&);
	void deleteEvent(CommandParser&);
	void showEvents(CommandParser);
	string undoCommand();
	string showFreeTime (CommandParser test);
	bool checkIfClash();
private:
	UpcomingHandler(void);
	static UpcomingHandler* uniqueObj;
	void fillDates(int);
	string generateId(Date eventDate);
	
	void showAllDeadlines();
	Event editDate(CommandParser test, Event eventObj);
	
	int getTimeArrayIndex(Time eventTime);
	string arrayIndexToString(int index);
	
};

