/*
Authors : Ishaan Singal, Raunak Rajpuria
MainLogic does the following
--Receives user input from the UI.
--Passes this input to CommandParser.
--Receives the deconstructed command from CommandParser.
--Passes valid command to ListHandler.
--Receives result from ListHandler.
--Formats result to be displayed.
--Writes to external storage.
--Returns formatted result to UI.
*/
#ifndef _MAINLOGIC_H
#define _MAINLOGIC_H

#include "CommandParser.h"
#include "ListHandler.h"
#include "UpcomingHandler.h"
#include "HistoryHandler.h"
#include "Date.h"
#include "Event.h"
#include "FileStorage.h"
#include "Time.h"

#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <stack>
#include <cassert>



using namespace std;

struct OutputText
{
	string statusMessage;
	string displayText;
};

class MainLogic
{
public:
	MainLogic();
	~MainLogic();

	void updateRecords();
	void processCommand( string );

	Date getCurrentSystemDate();
	string displayOutput();
	string getStatusMessage();

	bool checkIfReminder();
	string getReminderText();
	Time getCurrentSystemTime();
	bool readIfNextday ();
	string getLabel();

private:
	enum DISPLAYTYPE
	{
		PENDING=1,UPCOMING,OTHER
	};

	DISPLAYTYPE dtype;
	ListHandler* upcomingObj;
	ListHandler* historyObj;
	stack<DISPLAYTYPE> dtypeOrder;
	stack<string> commandOrder;
	string statusMessage;
	string outputDisplay;
	string label;

	void updateDisplayList();
	void updatePendingList();

	string getConvertedDate(string tempDate);
	string formatDisplayOutput();


	void processPending(CommandParser& test);
	void processUpcoming(CommandParser& test);
	void pushState(string);
	string undoLogic();

	void showWhenUpcoming(CommandParser test);
	void showWhenPending(CommandParser test);
	string getSuccessMessage(CommandParser test);
};

#endif