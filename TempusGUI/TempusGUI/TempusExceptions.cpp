#include "stdafx.h"
#include "TempusExceptions.h"

const string TempusException::INVALID_DATE_EXCEPTION = "Event Date Entered Is Invalid";
const string TempusException::MISSING_DATE_EXCEPTION = "Event Date Is Missing";
const string TempusException::INVALID_TIME_EXCEPTION = "Event Time Entered Is Invalid";
const string TempusException::MISSING_TIME_EXCEPTION = "Event Time Is Missing";
const string TempusException::MISSING_NAME_EXCEPTION = "Event Name Is Missing";
const string TempusException::INVALID_DEADLINE_EXCEPTION = "Event Deadline Entered Is Invalid";
const string TempusException::EXCESS_PARAMETERS_EXCEPTION = "Too Many Parameters Entered";
const string TempusException::MISSING_INDEX_EXCEPTION = "Event Index Is Missing";
const string TempusException::INVALID_INDEX_EXCEPTION = "Event Index Entered is Invalid";
const string TempusException::EMPTY_DISPLAY_EXCEPTION = "There Are No Events To Display";
const string TempusException::EMPTY_COMMAND_EXCEPTION = "No Command Entered";
const string TempusException::INVALID_COMMAND_EXCEPTION = "Command Entered Is Invalid";
const string TempusException::EVENT_CLASH_EXCEPTION = "Please Note That There is Another Event At The Same Time";
const string TempusException::INVALID_UNDO_EXCEPTION = "No Further Undo Action Available";
const string TempusException::FREE_DAY_EXCEPTION = "No events scheduled. You are free for the entire day";
const string TempusException::INVALID_EDIT_EXCEPTION = "Unable To Edit";
const string TempusException::INVALID_DELETE_EXCEPTION = "Unable To Delete";
TempusException::TempusException(string exceptionType, string message)
{
	errorMessage = exceptionType + ": " + message; 
}

TempusException::TempusException(string exceptionType)
{
	errorMessage = exceptionType; 
}

string TempusException::getMessage()
{
	return errorMessage;
}