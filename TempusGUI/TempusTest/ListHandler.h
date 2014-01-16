/*
Authors : Ishaan Singal, Raunak Rajpuria
ListHandler does the following: 
--Contains a list that stores all the events, along with a list that keeps track of what events are to be displayed on the screen. 
--Receives details of user command from MainLogic. 
--Performs the actions required for different tasks (add, delete, edit, search etc.) by making appropriate changes in the internal storage classes and updating its lists.
*/
#pragma once
#include "Date.h"
#include "CommandParser.h"


#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <stack>
#include <cassert>

using namespace std;

class ListHandler
{
protected:
	vector<Date> masterList;
	vector<Event> displayList;
	stack <string> commandOrder;
	stack <Event> eventOrder;
		
	void showParticularDate(Date dateToDisplay);
	void searchInputParameter(string stringToFind, string typeToSearch);
		
public:
	virtual void addEvent(CommandParser& test);
	virtual void editEvent(CommandParser &test);
	virtual void deleteEvent(CommandParser& test);
	virtual void showEvents(CommandParser test);
	void markAsDone(CommandParser& test);
	virtual void showPending();
	virtual string undoCommand();
	virtual string showFreeTime(CommandParser test); 
	virtual bool checkIfClash();
	
	void clearStack();
	void defaultList();
	string formatDisplayList();

	Date getCurrentDate();
	vector<Date> getMasterList();
	vector<Event> getDisplayList();
	ListHandler(void);
	~ListHandler(void);

private:
	
	Date getCurrentSystemDate();
};

