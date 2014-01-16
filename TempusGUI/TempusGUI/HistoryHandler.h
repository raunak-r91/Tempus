/*
Authors : Ishaan Singal, Raunak Rajpuria
HistoryHandler does the following:  
--Subclass of ListHandler class. It handles past events. 
--It is a singleton classes. Only one instance of this class can be created.
--Apart from inheriting the attributes and methods of the parent class, it has certain methods of its own to act on its type of list (i.e History).
*/
#pragma once
#include "ListHandler.h"

using namespace std;

class HistoryHandler : public ListHandler 
{

public:
	
	~HistoryHandler(void);
	static HistoryHandler* getInstance();
	void addEvent(CommandParser& test);
	void editEvent(CommandParser& test);
	void deleteEvent(CommandParser& test);
	void showEvents (CommandParser test);
	void showPending ();
	string undoCommand();
	
private:
	HistoryHandler(void);
	static HistoryHandler* uniqueObj;
	void fillDates(int);
};