/*
Authors : Ishaan Singal, Raunak Rajpuria
CommandParser does the following: 
--Receives user command from MainLogic.
--Tokenizes command into individual details according to keywords.
--Stores individual details as attributes.
--Checks validity of details entered.
--Returns result of validity check to MainLogic
*/
#include "stdafx.h"
#include "CommandParser.h"


CommandParser::CommandParser(void)
{
	string inputCommand="";
	string inputName="";
	string inputLocation="";
	string inputDate="";
	string inputIndex="";
	string inputTime="";
	inputEventType="se";
	eventStatus="nd";
}
void CommandParser::setInputCommand(KEYWORD currentCommand)
{
	switch(currentCommand)
	{
	case ADD:
		inputCommand="Add";
		break;

	case SHOW:
		inputCommand="Show";
		break;

	case DELETE:
		inputCommand="Delete";
		break;

	case DONE:
		inputCommand="Done";
		break;

	case EDIT:
		inputCommand="Edit";
		break;
	
	case HISTORY:
		inputCommand="History";
		break;

	case PENDING:
		inputCommand="Pending";
		break;

	case UNDO:
		inputCommand="Undo";
		break;

	case SFT:
		inputCommand="sft";
		break;

	case AGENDA:
		inputCommand="Agenda";
		break;

	default:
		inputCommand="Invalid";
		break;
	}
}
string CommandParser::getInputCommand()
{
	return inputCommand;
}
string CommandParser:: getInputName()
{
	return inputName;	
}
string CommandParser::getInputLocation()
{
	return inputLocation;
}
string CommandParser::getEventStatus()
{
	return eventStatus;
}
string CommandParser::getInputDate()
{
	return inputDate;
}
Date CommandParser:: getDateObj()
{
	return dateObj;
}
string CommandParser::getInputIndex()
{
	return inputIndex;		
}
string CommandParser::getInputTime()
{
	return inputTime;
}
Time CommandParser::getStartTimeObj()
{
	return startTime;		
}
Time CommandParser:: getEndTimeObj()
{
	return endTime;
}
string CommandParser::getInputEventType()
{
	return inputEventType;
}
CommandParser::KEYWORD CommandParser:: getKeyword (string keyWord){
	assert(keyWord!="");
	int i = 0;
	if (equalsIgnoreCase(keyWord,"Add"))
		i = 1;
	else if (equalsIgnoreCase(keyWord,"Show"))
		i = 2;
	else if (equalsIgnoreCase(keyWord,"Delete"))
		i = 3;
	else if (equalsIgnoreCase(keyWord,"Edit"))
		i = 4;
	else if (equalsIgnoreCase(keyWord,"Date"))
		i = 5;
	else if (equalsIgnoreCase(keyWord,"Location"))
		i = 6;
	else if (equalsIgnoreCase(keyWord,"Time"))
		i=7;
	else if (equalsIgnoreCase(keyWord,"Undo"))
		i=8;
	else if(equalsIgnoreCase(keyWord,"FTime"))
		i=9;
	else if (equalsIgnoreCase(keyWord,"By"))
		i=10;
	else if(equalsIgnoreCase(keyWord,"Done"))
		i=11;
	else if (equalsIgnoreCase(keyWord,"Pending"))
		i=12;
	else if (equalsIgnoreCase(keyWord,"History"))
		i=13;
	else if (equalsIgnoreCase(keyWord, "Agenda"))
		i=14;
	else
		i=15;
	return KEYWORD(i);
}
string CommandParser:: getFirstWord(string command)
{
	stringstream strstr;
	string firstWord;
	strstr << command;
	strstr >> firstWord;
	return firstWord;
}
int CommandParser::findDateKeyword(string userCommand)
{
	int index=-1;
	string searchCommand = toLower(userCommand);
	string dateKeywords[]={" today", " tomorrow", " monday", " tuesday", " wednesday", " thursday", " friday", " saturday", " sunday"};
	for(int i=0; i < 9; i++)
	{
		index=searchCommand.find(dateKeywords[i]);
		if(index!=-1)
			break;
	}
	return index;
}
string CommandParser:: updateDateKeywords(string userCommand)
{
	int index;
	index=findDateKeyword(userCommand);
	
	if(index!=-1)
		userCommand.insert(index+1, "Date ");
	return userCommand;
}
int CommandParser::getNextKeywordIndex(vector<string>tokenized, int start)
{
	int i=0;
	for (i=start; i<tokenized.size();i++)
	{
		if (isKeyword(tokenized[i]))
			break;
	}
	return i;
}
string CommandParser::updateDefaultCase(string userCommand)
{
	if (!isKeyword(getFirstWord(userCommand)))
		userCommand.insert(0,"Add ");
	return userCommand;
}
void CommandParser::setInputDetails(string userCommand)
{
	KEYWORD currentKeyword, firstKeyword;
	int nextKeywordIndex;
	string completeElement;
	vector<string> tokenizedList;
	
	userCommand=trim(userCommand, " ");//trim space from front and back
	if(userCommand=="")
		throw TempusException(TempusException::EMPTY_COMMAND_EXCEPTION);
	
	userCommand = updateDateKeywords(userCommand);
	userCommand = updateDefaultCase(userCommand);
	
	tokenizedList = tokenize (userCommand);
	firstKeyword=getKeyword(tokenizedList[0]);
	setInputCommand(firstKeyword);
	
	for (int i =0; i<tokenizedList.size(); i++)
	{
		currentKeyword = getKeyword(tokenizedList[i]);
		nextKeywordIndex=getNextKeywordIndex(tokenizedList, i+1);
		completeElement = getCompleteElement(tokenizedList, i, nextKeywordIndex);
		setCompleteElement(currentKeyword, completeElement);
		i=nextKeywordIndex-1;
	}
	return;
}
string CommandParser::getCompleteElement(vector<string>tokenizedList, int startindex, int endindex)
{
	string completeElement="";
	for(int i =startindex+1; i<endindex; i++)
	{
		completeElement += tokenizedList[i];
		completeElement += " ";
	}
	completeElement = trim (completeElement, " ");//trim space from front and back
	return completeElement;
}
void CommandParser:: setCompleteElement(KEYWORD currentKeyword, string completeElement)
{
	Date systemDate;
	switch(currentKeyword)
	{
	case ADD:
		inputName = completeElement;
		break;
		
	case SHOW:
		if (equalsIgnoreCase(completeElement,"deadline"))
			inputEventType = "d";
		else
			inputName = completeElement;
		break;

	case DAY:
		inputDate = completeElement;
		systemDate= getCurrentSystemDate();
		dateObj = systemDate.dateStringToObject(inputDate);
		break;

	case LOCATION:
		inputLocation = completeElement;
		break;
	
	case DELETE:
		inputIndex = completeElement;
		break;
	
	case DONE:
		inputIndex=completeElement;
		break;

	case TIME:
		inputTime = completeElement;
		inputEventType="se";
		setStartEndTime();
		break;

	case BY:
		inputTime = completeElement;
		inputEventType = "d";
		setStartEndTime();
		break;

	case EDIT:
		inputIndex=getFirstWord(completeElement);
		inputName = removeFirstWord(completeElement);
		break;
	}

	if(hasName() && hasSlash(inputName))
		inputName=removeSlash(inputName);
	if(hasLocation() && hasSlash(inputLocation))
		inputLocation=removeSlash(inputLocation);

	return;
}

bool CommandParser::hasSlash (string input)
{
	int pos=input.find('/');
	if(pos>-1)
		return true;
	return false;
}
string CommandParser::removeSlash (string input)
{
	string result="";
	int pos=input.find('/');
	result+=input.substr(0,pos);
	result+=input.substr(pos+1);
	return result;
}

void CommandParser::setStartEndTime()
{
	int posHyphen;

	if(!hasTime())
		return;
	if (hasHyphen())
	{
		posHyphen = getHyphenPosition(inputTime);
		startTime.timeStringToObject(inputTime.substr(0,posHyphen));
		endTime.timeStringToObject(inputTime.substr(posHyphen+1));//Why the 2nd part in substr??
	}
	
	else
		startTime.timeStringToObject(inputTime);
}
bool CommandParser:: isKeyword(string word)
{
	bool flag=false;
	if (getKeyword(word)!=INVALID)
		flag=true;
	return flag;
}
string CommandParser ::removeFirstWord(string  command)
{	
	string buffer;
	string statementWithFirstWordRemoved=" ";
	stringstream formattedCommand(command);
	formattedCommand >> buffer;
	while(formattedCommand >> buffer)
	{
		statementWithFirstWordRemoved+=buffer+" ";
	}
	statementWithFirstWordRemoved=trim(statementWithFirstWordRemoved, " ");//trim space from front and back
	return statementWithFirstWordRemoved;
}
bool CommandParser::hasName()
{
	if(inputName=="")
		return false;
	return true;
}
bool CommandParser::hasLocation()
{
	if(inputLocation=="")
		return false;
	return true;
}
bool CommandParser::hasIndex()
{
	if(inputIndex=="")
		return false;
	return true;
}
bool CommandParser::hasTime()
{
	if(inputTime=="")
		return false;
	return true;
}
bool CommandParser::hasDate()
{
	if(inputDate=="")
		return false;
	return true;
}
bool CommandParser::isValidInput()
{
	bool flag = false;
	if (equalsIgnoreCase(inputCommand,"Add"))
	{
		if (isValidAdd())
			flag= true;
	}
	else if (equalsIgnoreCase(inputCommand,"Show"))
	{
		if (isValidShow())
			flag=true;
	}
	else if (equalsIgnoreCase(inputCommand,"Edit"))
	{
		if (isValidEdit())
			flag=true;
	}
	else if (equalsIgnoreCase(inputCommand,"sft"))
	{
		if (isValidSft())
			flag=true;
	}
	
	else if (equalsIgnoreCase(inputCommand,"Delete"))
	{
		if (isValidDelete())
			flag=true;
	}
	else if (equalsIgnoreCase(inputCommand,"History") || equalsIgnoreCase(inputCommand,"Pending")||equalsIgnoreCase(inputCommand, "Undo") || equalsIgnoreCase(inputCommand,"Agenda"))
			flag=true;
	else if (equalsIgnoreCase(inputCommand,"Done"))
	{
		if (isValidDone())
			flag=true;
	}
	
	return flag;
}
bool CommandParser::isValidAdd()
{
	bool flag = false;
	if (isValidName() && isValidTime() &&isValidEditAddDate())
		flag = true;
	return flag;
}
bool CommandParser::isValidName()
{
	if (!hasName())
		throw TempusException(TempusException::MISSING_NAME_EXCEPTION, "Event Name Is Compulsory");
	return true;
}
bool CommandParser::hasHyphen()
{
	if(getHyphenPosition(inputTime)!=-1)
		return true;
	return false;
}
bool CommandParser::isDeadline()
{
	if(inputEventType=="d")
		return true;
	return false;
}
bool CommandParser::hasStartTime()
{
	if(startTime.getAmPm()=="")
		return false;
	return true;
}
bool CommandParser::hasEndTime()
{
	if(endTime.getAmPm()=="")
		return false;
	return true;
}

bool CommandParser::isValidTime()
{
	bool flag= true;
	
	if (hasTime())
	{
		if (hasEndTime() && isDeadline())
			throw TempusException(TempusException::INVALID_DEADLINE_EXCEPTION, "Deadlines Cannot Have End Time");

		else if (hasStartTime() && hasEndTime() && !isDeadline())
		{
			if (!startTime.isValidTime())
				throw TempusException(TempusException::INVALID_TIME_EXCEPTION, "Start Time Is Invalid");
			if (!endTime.isValidTime())
				throw TempusException(TempusException::INVALID_TIME_EXCEPTION, "End Time Is Invalid");
			if (!endTime.isGreaterThan(startTime))
				throw TempusException(TempusException::INVALID_TIME_EXCEPTION, "Start Time Cannot Be Greater Than End Time");
		
		}
		if (hasStartTime() && !hasEndTime())
		{
			if (!startTime.isValidTime())
				TempusException(TempusException::INVALID_TIME_EXCEPTION, "Start Time Is Invalid");
			
		}
		if(!hasStartTime())
			throw TempusException(TempusException::INVALID_TIME_EXCEPTION, "Start Time Is Invalid");
	}
	else 
		throw TempusException(TempusException::MISSING_TIME_EXCEPTION, "Event Time Is Compulsory");
	return flag;
}
bool CommandParser::isValidDate()
{
	bool flag=false;
	Date systemDate = getCurrentSystemDate();
	if (hasDate())
	{
		if (systemDate.isValidDate(dateObj))
			flag = true;
		else
			throw TempusException(TempusException::INVALID_DATE_EXCEPTION);
	}
	else
		throw TempusException(TempusException::MISSING_DATE_EXCEPTION, "Event Date Is Compulsory");
	return flag;
}
bool CommandParser::isValidEditAddDate()
{
	bool flag = false;
	Date systemDate = getCurrentSystemDate();
	if (isValidDate())
	{
		if (systemDate.compareDates(dateObj)>=0)
			flag = true;
		else
			throw TempusException(TempusException::INVALID_DATE_EXCEPTION, "Date Entered Is Before The Current Date");
	}
	
	return flag;
	
}
bool CommandParser::isValidEdit()
{
	bool flag = false;
	
	if (hasName())
		if (isValidName())
			flag = true;
	
	if (hasTime())
		if (isValidTime())
			flag = true;
	
	if (hasDate())
		if (isValidEditAddDate())
			flag = true;
	
	if (isValidIndex())
		flag = true;
	
	return flag;
}
bool CommandParser::isValidShow()
{
	bool flag= true;
	int count=0;
	if (hasName())
	{
		flag =true;
		count++;
	}
	if (hasLocation())
	{
		flag=true;
		count++;
	}
	if (hasDate())
	{
		if (isValidDate())
		{
			count++;
			flag =true;
		}
		
	}
	if (count>1)
		throw TempusException(TempusException::EXCESS_PARAMETERS_EXCEPTION);
	
	return flag;
}

bool CommandParser::isValidSft()
{
	bool flag = false;
	
	if (isValidEditAddDate())
		flag =true;
	
	return flag;
}
bool CommandParser::isValidDelete()
{
	if (isValidIndex())
		return true;
	return false;
}
bool CommandParser::isValidDone()
{
	if(!hasIndex())
		return true;
	if (isValidIndex())
		return true;
	return false;
}

bool CommandParser::isValidIndex()
{
	bool flag= false;
	vector<string> tokenized=tokenize(inputIndex);
	
	if (tokenized.size()==0)
		throw TempusException(TempusException::MISSING_INDEX_EXCEPTION, "Index Is Compulsory");
	else if(tokenized.size()>1)
		throw TempusException(TempusException::INVALID_INDEX_EXCEPTION);
	else
	{
		int index = atoi(inputIndex.c_str());
		if (index<1)
			throw TempusException(TempusException::INVALID_INDEX_EXCEPTION);
		flag = true;
	}
	return flag;
}

string CommandParser::getId()
{
	return id;
}
void CommandParser::setId(string idToSet)
{
	id=idToSet;
}
Date CommandParser::getCurrentSystemDate()
{
	time_t t=time(0);
	tm* now=localtime(&t);
	Date obj;
	obj.setDay(now->tm_mday);
	obj.setMonth(now->tm_mon+1);
	obj.setYear(now->tm_year + 1900);
	return obj;
}
int CommandParser::getHyphenPosition(string text)
{
	int pos=text.find('-');
	if(pos>-1)
		return pos;
	return -1;
}
bool CommandParser::hasWords()
{
	if (!hasName() && !hasTime() && !hasDate()&& !hasLocation() && inputEventType!="d")
		return false;
	else
		return true;
}
void CommandParser::setStatus(string statusToSet)
{
	eventStatus=statusToSet;
}
void CommandParser::setObjectDetails(Event eventObj)
{
	inputName=eventObj.getName();
	inputLocation=eventObj.getLocation();
	startTime=eventObj.getStartTime();
	endTime=eventObj.getEndTime();
	id=eventObj.getId();
	inputEventType=eventObj.getEventType();
	eventStatus=eventObj.getEventStatus();
}
string CommandParser::getEventDetails()
{
	stringstream output;
	
	output << getInputName();
	if (getInputEventType()=="d")
		output << " by ";
	else
		output << " at ";
	output << getStartTimeObj().formatCompleteTime(getEndTimeObj());
	if (getInputLocation()!="")
		output << " at "<< getInputLocation();
	output << endl;

	return output.str();
}
CommandParser::~CommandParser(void)
{
}
