/*
Authors : Ishaan Singal, Raunak Rajpuria
HistoryHandler does the following:  
--Subclass of ListHandler class. It handles past events. 
--It is a singleton classes. Only one instance of this class can be created.
--Apart from inheriting the attributes and methods of the parent class, it has certain methods of its own to act on its type of list (i.e History).
*/

#include "HistoryHandler.h"

HistoryHandler* HistoryHandler::uniqueObj=NULL; 
HistoryHandler::HistoryHandler(void) : ListHandler()
{
}

HistoryHandler* HistoryHandler::getInstance()
{
	if(uniqueObj==NULL)
		uniqueObj=new HistoryHandler();
	return uniqueObj;
}
void HistoryHandler::fillDates(int index)
{
	Date temp=masterList[masterList.size()-1];
	Date temp1;
	for (int i = masterList.size(); i <=index; i++)
	{
		temp.decrementDays(1);
		temp1.setDay(temp.getDay());
		temp1.setMonth(temp.getMonth());
		temp1.setYear(temp.getYear());
		masterList.push_back(temp1);
	}
}

void HistoryHandler::addEvent (CommandParser& test)
{
	int index = masterList[0].dateDifference(test.getDateObj());
	if (masterList.size()<=index)
		fillDates(index);
	
	masterList[index].addEvent(	test.getId(), 
								test.getInputName(), 
								test.getInputLocation(), 
								test.getStartTimeObj(), 
								test.getEndTimeObj(), 
								test.getInputEventType(), 
								test.getEventStatus());	
}
void HistoryHandler::deleteEvent (CommandParser& test)
{
	int displayIndex, i;
		
	displayIndex=atoi(test.getInputIndex().c_str());
	string eventId = displayList[displayIndex-1].getId();
	string date=eventId.substr(0,8);
	Date dateObj=masterList[0].dateStringToObject(date);
	int dateIndex=masterList[0].dateDifference(dateObj);
	int indexToDelete=masterList[dateIndex].getIndex(eventId);
			
	commandOrder.push("Delete");
	eventOrder.push(masterList[dateIndex].getEvent(indexToDelete));
	masterList[dateIndex].deleteEvent(indexToDelete);
}
void HistoryHandler::editEvent (CommandParser& test)
{
	int displayIndex=atoi(test.getInputIndex().c_str());
	if(displayIndex>displayList.size())
		throw TempusException(TempusException::INVALID_INDEX_EXCEPTION);
	if(!test.hasWords())
		throw TempusException(TempusException::INVALID_EDIT_EXCEPTION, "No Details Entered");
	if(!test.hasDate())
		throw TempusException(TempusException::INVALID_EDIT_EXCEPTION, "Only Date Can Be Edited In Archive");
	string id = displayList[displayIndex-1].getId();
	string date=id.substr(0,8);
	Date dateObj=masterList[0].dateStringToObject(date);
	int dateIndex=masterList[0].dateDifference(dateObj);
	int indexToEdit=masterList[dateIndex].getIndex(id);

	assert(indexToEdit!=-1);

	Event eventObj2 = masterList[dateIndex].getEvent(indexToEdit);
	if (test.hasTime() && !test.hasDate())
		throw TempusException(TempusException::INVALID_EDIT_EXCEPTION, "Cannot Edit Time In Archive");
	deleteEvent(test);
		
	stringstream input;
	input << eventObj2.getName();
	if (eventObj2.getLocation()!="")
		input << " Location " << eventObj2.getLocation();
	input << " Date " << test.getInputDate();
	if (eventObj2.getEventType()!="d")
		input << " Time ";
	else
		input << " By ";
	
	if (test.hasTime())
		input << test.getStartTimeObj().formatCompleteTime(test.getEndTimeObj());
	else
		input  << eventObj2.getStartTime().formatCompleteTime(eventObj2.getEndTime());

	test.setStatus(eventObj2.getEventStatus());
	test.setInputDetails(input.str());
}

void HistoryHandler::showPending ()
{
	displayList.clear();
	int size=masterList.size()<4?masterList.size():4;
	for (int i =0; i < size ;i++)
	{
		for (int j = 0; j<masterList[i].getEventListLength(); j++)
		{
			if(masterList[i].getEvent(j).getEventStatus()=="nd")
				displayList.push_back(masterList.at(i).getEvent(j));
		}
	}
}
string HistoryHandler:: undoCommand ()
{
	string commandType=commandOrder.top();
	commandOrder.pop();
	Event eventObj=eventOrder.top();
	eventOrder.pop();

	Date dateToUndo=masterList[0].dateStringToObject(eventObj.getId().substr(0,8));
	int index = masterList[0].dateDifference(dateToUndo);
	
	if(equalsIgnoreCase(commandType,"Done"))
	{
		masterList[index].markEventAsNotDone(masterList[index].getIndex(eventObj.getId()));
		return commandType;
	}
	else if(equalsIgnoreCase(commandType,"Done All"))
	{
		while(commandType=="Done All")
		{
			masterList[index].markEventAsNotDone(masterList[index].getIndex(eventObj.getId()));
			if (commandOrder.size()>0)
			{
				if(commandOrder.top()=="Done All")
				{
					commandType=commandOrder.top();
					eventObj=eventOrder.top();
					dateToUndo=masterList[0].dateStringToObject(eventObj.getId().substr(0,8));
					index = masterList[0].dateDifference(dateToUndo);
					commandOrder.pop();
					eventOrder.pop();
				}
			}
			else
				break;
		}
		return "Done All";
	}
	if (equalsIgnoreCase(commandType, "Delete"))
	{
		masterList[index].addEvent(eventObj.getId(),eventObj.getName(), eventObj.getLocation(), eventObj.getStartTime(), eventObj.getEndTime(), eventObj.getEventType(), eventObj.getEventStatus());
		return commandType;
	}
}
void HistoryHandler::showEvents (CommandParser test)
{
	Date date;
	if (test.hasName())
	{
		displayList.clear();
		searchInputParameter(test.getInputName(), "name");
	}
	
	else if (test.hasDate())
	{
		showParticularDate(test.getDateObj());
	}

	else if (test.hasLocation())
	{
		displayList.clear();
		searchInputParameter(test.getInputLocation(), "location");
	}
}

HistoryHandler::~HistoryHandler(void)
{
}
