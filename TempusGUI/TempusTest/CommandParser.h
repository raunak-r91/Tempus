/*
Authors : Ishaan Singal, Raunak Rajpuria
CommandParser does the following: 
--Receives user command from MainLogic.
--Tokenizes command into individual details according to keywords.
--Stores individual details as attributes.
--Checks validity of details entered.
--Returns result of validity check to MainLogic
*/
#pragma once

#include "Time.h"
#include "Date.h"
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <stack>
#include <cassert>

using namespace std;

class CommandParser
{



private:
	string inputCommand;
	string inputName;
	string inputLocation;
	string inputDate;
	string inputIndex;
	string inputTime;
	string inputEventType;
	string eventStatus;
	string id;
	Time startTime;
	Time endTime;
	Date dateObj;
	
	enum KEYWORD 
	{	
	ADD=1, SHOW, DELETE, EDIT, DAY, LOCATION, TIME, UNDO, SFT, BY, DONE, PENDING, HISTORY, AGENDA, INVALID
	};

	void setInputCommand(KEYWORD currentCommand);
	KEYWORD  getKeyword(string);
	bool isCommand(string word);
	bool isKeyword(string word);

	int findDateKeyword(string userCommand);
	string updateDateKeywords(string userCommand);
	
	string getFirstWord(string command);
	string removeFirstWord(string  command);

	int getHyphenPosition(string text);

	string updateDefaultCase(string userCommand);
	int getNextKeywordIndex(vector<string>tokenized, int);
	string getCompleteElement(vector<string>tokenizedList, int startindex, int endindex);
	void setCompleteElement(KEYWORD currentCommand, string completeElement);
	void setStartEndTime();

	
	bool hasHyphen();
	
	bool isValidAdd();
	bool isValidName();
	bool isValidTime();
	bool isValidDate();
	bool isValidShow();
	bool isValidEdit();
	bool isValidSft();
	bool isValidIndex();
	bool isValidDone();
	bool isValidDelete();
	bool isValidEditAddDate();
	Date getCurrentSystemDate();
	string removeSlash (string input);
	bool hasSlash(string input);

public:
	CommandParser(void);
	string getInputCommand();
	string getInputName();
	string getInputLocation();
	string getInputDate();
	string getEventStatus();
	string getInputIndex();
	string getInputTime();
	string getId();
	string getInputEventType();
	Time getStartTimeObj();
	Time getEndTimeObj();
	Date getDateObj();
	void setId(string idToSet);
	void setStatus(string statusToSet);
	void setInputDetails(string userCommand);
	bool isValidInput();
	bool hasWords();
	void setObjectDetails(Event eventObj);
	string getEventDetails();

	bool hasName();
	bool hasLocation();
	bool hasIndex();
	bool hasTime();
	bool hasDate();
	bool hasStartTime();
	bool hasEndTime();
	bool isDeadline();

	~CommandParser(void);
};

