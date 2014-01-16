/*
Authors : Ishaan Singal, Raunak Rajpuria
ListHandler does the following: 
--Contains a list that stores all the events, along with a list that keeps track of what events are to be displayed on the screen. 
--Receives details of user command from MainLogic. 
--Performs the actions required for different tasks (add, delete, edit, search etc.) by making appropriate changes in the internal storage classes and updating its lists.
*/
#include "ListHandler.h"

Date ListHandler::getCurrentSystemDate()
{
	time_t t=time(0);
	tm* now=localtime(&t);
	Date obj;
	obj.setDay(now->tm_mday);
	obj.setMonth(now->tm_mon+1);
	obj.setYear(now->tm_year + 1900);
	return obj;
}
ListHandler::ListHandler(void)
{
	Date obj=getCurrentSystemDate();
	masterList.push_back(obj);
}

void ListHandler::clearStack()
{
	while(!eventOrder.empty())
	{
		eventOrder.pop();
		commandOrder.pop();
	}
}

Date ListHandler::getCurrentDate()
{
	return masterList[0];
}
vector<Date> ListHandler::getMasterList()
{
	return masterList;
}
vector<Event> ListHandler::getDisplayList()
{
	return displayList;
}

void ListHandler::defaultList()
{
	displayList.clear();
	for (int i =0; i < masterList.size();i++)
		for (int j = 0; j<masterList[i].getEventListLength(); j++)
			displayList.push_back(masterList.at(i).getEvent(j));
}
void ListHandler::addEvent(CommandParser& test)
{}
void ListHandler::editEvent(CommandParser& test)
{}
void ListHandler::deleteEvent(CommandParser& test)
{}
void ListHandler::showEvents(CommandParser test)
{}
bool ListHandler::checkIfClash()
{
	return false;
}


void ListHandler::markAsDone(CommandParser& test)
{
	int displayIndex;
	if(test.hasIndex())
	{
		displayIndex=atoi(test.getInputIndex().c_str());
		assert(displayIndex>0);
		if(displayIndex>displayList.size())
			throw TempusException(TempusException::INVALID_INDEX_EXCEPTION);
	
		string id = displayList[displayIndex-1].getId();
		string date=id.substr(0,8);
		Date dateObj=masterList[0].dateStringToObject(date);
		int dateIndex=masterList[0].dateDifference(dateObj);
		int indexToMark=masterList[dateIndex].getIndex(id);
	
		assert (indexToMark!=-1);

		commandOrder.push("Done");
		eventOrder.push(masterList[dateIndex].getEvent(indexToMark));
		test.setObjectDetails(masterList[dateIndex].getEvent(indexToMark));
		masterList[dateIndex].markEventAsDone(indexToMark);
	}
	else
	{
		for(int i=0;i<displayList.size();i++)
		{
			
			string id = displayList[i].getId();
			string date=id.substr(0,8);
			Date dateObj=masterList[0].dateStringToObject(date);
			int dateIndex=masterList[0].dateDifference(dateObj);
			int indexToMark=masterList[dateIndex].getIndex(id);
	
			assert (indexToMark!=-1);
			if (masterList[dateIndex].getEvent(indexToMark).getEventStatus()!="d")
			{
				commandOrder.push("Done All");
				eventOrder.push(masterList[dateIndex].getEvent(indexToMark));
				test.setObjectDetails(masterList[dateIndex].getEvent(indexToMark));
				masterList[dateIndex].markEventAsDone(indexToMark);
			}
		}
	}

	
	return;
}
void ListHandler::showPending()
{}

string ListHandler::undoCommand()
{ return "";}

string ListHandler::showFreeTime(CommandParser test)
{
	return ""; 
}

void ListHandler::showParticularDate(Date dateToDisplay)
{
	
	int index;
	Date currentDate=masterList[0];

	index = masterList[0].dateDifference(dateToDisplay);
	if (index>=masterList.size())
	{
		defaultList();
		throw TempusException(TempusException::EMPTY_DISPLAY_EXCEPTION);
	}
	else
		displayList = masterList[index].getEventList();
	
	if(displayList.size()==0)
	{
		defaultList();
		throw TempusException(TempusException::EMPTY_DISPLAY_EXCEPTION);
	}
	return;
}
void ListHandler::searchInputParameter(string stringToFind, string typeToSearch)
{
	string stringToCompare ="";
	displayList.clear();
	
	for (int i =0; i <masterList.size();i++)
	{
		for (int j = 0; j<masterList[i].getEventList().size(); j++)
		{
			if (equalsIgnoreCase(typeToSearch,"name"))
				stringToCompare=masterList[i].getEvent(j).getName();
			else if (equalsIgnoreCase(typeToSearch, "location"))
				stringToCompare=masterList[i].getEvent(j).getLocation();

			if (hasString(stringToFind, stringToCompare))
				displayList.push_back(masterList[i].getEvent(j));
		}
	}
	if(displayList.size()==0)
	{
		defaultList();
		throw TempusException(TempusException::EMPTY_DISPLAY_EXCEPTION);
	}
	return;
}

string ListHandler::formatDisplayList()
{
	Event currentEvent;
	string displayDate="";
	string prevDate="";
	stringstream output;
	Date tempDate;

	for (int i =0; i<displayList.size(); i++)
	{
		displayDate = displayList[i].getId().substr(0,8);
		tempDate = getCurrentSystemDate().dateStringToObject(displayDate);
		displayDate = tempDate.getConvertedDate(displayDate);
		
		if (displayDate!=prevDate)
		{
			prevDate=displayDate;
			output <<"\t\t";
			if(tempDate.compareDates(getCurrentSystemDate())==0)
				output << "\t  Today";
			else if(tempDate.compareDates(getCurrentSystemDate())==-1)
				output << "\tTomorrow";
			else
				output << displayDate;
			output << endl;
		}
		if(i<9)
			output << " ";
		output << "["<< i+1 << "] \t" << displayList[i].getEventDetails();
		
	}
	return output.str();
}

ListHandler::~ListHandler(void)
{
}
