#pragma once

#include <string>
using namespace std;

class TempusException
{
public:

	static const string INVALID_DATE_EXCEPTION;
	static const string MISSING_DATE_EXCEPTION; 
	static const string INVALID_TIME_EXCEPTION;
	static const string MISSING_TIME_EXCEPTION;
	static const string MISSING_NAME_EXCEPTION;
	static const string INVALID_DEADLINE_EXCEPTION;
	static const string EXCESS_PARAMETERS_EXCEPTION;
	static const string MISSING_INDEX_EXCEPTION;
	static const string INVALID_INDEX_EXCEPTION;
	static const string EMPTY_DISPLAY_EXCEPTION;
	static const string EMPTY_COMMAND_EXCEPTION; 
	static const string INVALID_COMMAND_EXCEPTION;
	static const string EVENT_CLASH_EXCEPTION;
	static const string INVALID_UNDO_EXCEPTION;
	static const string FREE_DAY_EXCEPTION;
	static const string INVALID_EDIT_EXCEPTION;
	static const string INVALID_DELETE_EXCEPTION;

	TempusException(string);
	TempusException(string, string);
	string getMessage();

private:
	string errorMessage;
};