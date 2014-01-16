/*
Authors : Ishaan Singal, Raunak Rajpuria
UpcomingHandler does the following:  
--Subclasses of ListHandler class. It handles upcoming events. 
--It is a singleton class. Only one instance of this class can be created.
--Apart from inheriting the attributes and methods of the parent class, it has certain methods of its own to act on its type of list (i.e Upcoming).
*/
#include "UpcomingHandler.h"

UpcomingHandler* UpcomingHandler::uniqueObj=NULL; 
UpcomingHandler::UpcomingHandler(void) : ListHandler()
{
}

void UpcomingHandler::fillDates(int index)
{
	Date temp=masterList[masterList.size()-1];
	Date temp1;
	for (int i = masterList.size(); i <=index; i++)
	{
		temp.incrementDays(1);
		temp1.setDay(temp.getDay());
		temp1.setMonth(temp.getMonth());
		temp1.setYear(temp.getYear());
		masterList.push_back(temp1);
	}
}


UpcomingHandler* UpcomingHandler::getInstance()
{
	if(uniqueObj==NULL)
		uniqueObj=new UpcomingHandler();
	return uniqueObj;
}
string UpcomingHandler::generateId(Date eventDate)
{
	string eventId="";
	stringstream temp;
	Event tempEvent;
	int day=eventDate.getDay();
	int month=eventDate.getMonth();
	int year=eventDate.getYear();
	double newId = 0;
	string currentId="", prevId="";

	
	if (eventDate.getEventListLength() >0)
	{
		eventId = eventDate.getLargestId();
		newId = atoi(eventId.substr(8,2).c_str() ) + 1;
		temp << eventId.substr(0,8).c_str();
		if (newId < 10)
			temp << '0';
		temp << newId;
	}
	else
	{
		if(day<10)
			temp << 0 << day;
		else temp<< day;
		
		if(month < 10)
			temp << 0 << month;
		else temp << month;
		
		temp << year;
		temp << "01";
	}
	eventId = temp.str();
	return eventId;
}

void UpcomingHandler::addEvent(CommandParser& test)
{
	Date dateToAdd=test.getDateObj();
	int index = masterList[0].dateDifference(dateToAdd);
	
	if (masterList.size()<=index)
		fillDates(index);

	string objUniqueId = test.getId();
	if(objUniqueId=="")
	{
		objUniqueId= generateId(masterList[index]);
		test.setId(objUniqueId);
	}

	masterList[index].addEvent(objUniqueId, 
								test.getInputName(), 
								test.getInputLocation(), 
								test.getStartTimeObj(), 
								test.getEndTimeObj(),
								test.getInputEventType(),
								test.getEventStatus());
				
	commandOrder.push("Add");
	eventOrder.push(masterList[index].getEvent(masterList[index].getIndex(objUniqueId)));
	return;
}

void UpcomingHandler::editEvent(CommandParser &test)
{
	Event eventObj, prevObj;
	int displayIndex, i;
	displayIndex=atoi(test.getInputIndex().c_str());

	assert(displayIndex>0);

	if(displayIndex>displayList.size())
		throw TempusException(TempusException::INVALID_INDEX_EXCEPTION);
	if(!test.hasWords())
		throw TempusException(TempusException::INVALID_EDIT_EXCEPTION, "No Details Entered");
	
	string id = displayList[displayIndex-1].getId();
	string date=id.substr(0,8);
	Date dateObj=masterList[0].dateStringToObject(date);
	int dateIndex=masterList[0].dateDifference(dateObj);
	int eventIndexToEdit=masterList[dateIndex].getIndex(id);
	
	eventObj = masterList[dateIndex].getEvent(eventIndexToEdit);
	prevObj= masterList[dateIndex].getEvent(eventIndexToEdit);
	assert(eventIndexToEdit>=0);
	
	if (test.hasTime())
	{
		if(eventObj.getEventType()=="se" && test.isDeadline())
			masterList[dateIndex].editEventTimeToDeadline(eventIndexToEdit, test.getStartTimeObj(), test.getEndTimeObj());
		else
			masterList[dateIndex].editEventTime(eventIndexToEdit, test.getStartTimeObj(), test.getEndTimeObj());
		eventIndexToEdit=masterList[dateIndex].getIndex(id);
		eventObj = masterList[dateIndex].getEvent(eventIndexToEdit);
	}

	if (test.hasName())
		masterList[dateIndex].editEventName(eventIndexToEdit, test.getInputName());
	if (test.hasLocation())
		masterList[dateIndex].editEventLocation(eventIndexToEdit, test.getInputLocation());
	
	if (test.hasDate())
	{
		eventObj = masterList[dateIndex].getEvent(eventIndexToEdit);
		eventObj= editDate(test,eventObj);
	}
	
	eventOrder.push(displayList[displayIndex-1]);
	eventOrder.push(eventObj);
	test.setObjectDetails(prevObj);
	commandOrder.push("edit");
	commandOrder.push("edit");
	
	return;
}

Event UpcomingHandler::editDate(CommandParser test, Event eventObj)
{
	deleteEvent(test);
	commandOrder.pop();//to pop out the extra values pushed by helper delete
	eventOrder.pop();

	int dateIndex = masterList[0].dateDifference(test.getDateObj());
		
	if (masterList.size()<=dateIndex)
		fillDates(dateIndex);

	string newId = generateId(masterList[dateIndex]);
	masterList[dateIndex].addEvent(newId,
									eventObj.getName(),
									eventObj.getLocation(),
									eventObj.getStartTime(),
									eventObj.getEndTime(),
									eventObj.getEventType(),
									eventObj.getEventStatus());
	
	eventObj=masterList[dateIndex].getEvent(masterList[dateIndex].getIndex(newId));
	return eventObj;
}

void UpcomingHandler::deleteEvent(CommandParser& test)
{
	int displayIndex, i;
	Event eventObj;
	
	displayIndex=atoi(test.getInputIndex().c_str());
	if(displayIndex>displayList.size())
		throw TempusException(TempusException::INVALID_INDEX_EXCEPTION);
	
	string id = displayList[displayIndex-1].getId();
	string currentDate=id.substr(0,8);
	Date dateObj=masterList[0].dateStringToObject(currentDate);
	int dateIndex=masterList[0].dateDifference(dateObj);
	int indexToDelete=masterList[dateIndex].getIndex(id);

	assert (indexToDelete!=-1);
	
	eventObj=masterList[dateIndex].getEvent(indexToDelete);
	test.setObjectDetails(eventObj);
	masterList[dateIndex].deleteEvent(indexToDelete);
		
	commandOrder.push("delete");
	eventOrder.push(eventObj);
}

void UpcomingHandler::showEvents(CommandParser test)
{
	Date date;
	if (test.hasName())
		searchInputParameter(test.getInputName(),"name");

	else if (test.getInputEventType()=="d")
		showAllDeadlines ();

	else if (test.hasDate())
		showParticularDate(test.getDateObj());

	else if (test.hasLocation())
		searchInputParameter(test.getInputLocation(), "location");

	return;
}

void UpcomingHandler::showAllDeadlines()
{
	displayList.clear();
	for (int i =0; i <masterList.size();i++)
	{
		for (int j = 0; j<masterList[i].getEventListLength(); j++)
		{
			if (masterList[i].getEvent(j).getEventType()=="d")
				displayList.push_back(masterList.at(i).getEvent(j));
		}
	}
	if(displayList.size()==0)
	{
		defaultList();
		throw TempusException(TempusException::EMPTY_DISPLAY_EXCEPTION, "No Deadlines Scheduled");
	}
	return;
}

string UpcomingHandler::showFreeTime (CommandParser test)
{
	bool flag = true;
	bool hasDeadlines = false;
	Date date;
	int i,k;
	vector<Event> eventList;
	stringstream output;
	vector<Event>* timeArray[24];
	int start=7,end=7; //show free times shows time only from 7am to 12am

	for(int j=0;j<24;j++)
		timeArray[j]=new vector<Event>;
	
	int index,arrayIndex;
	Date currentDate=masterList[0];
	Date dateToDisplay=test.getDateObj();
		
	index = currentDate.dateDifference(dateToDisplay);
	if(index>masterList.size()-1)
		throw TempusException(TempusException::FREE_DAY_EXCEPTION);
	
	eventList=masterList[index].getEventList();
	if(eventList.size()==0)
		throw TempusException(TempusException::FREE_DAY_EXCEPTION);
	for(int j=0;j<eventList.size();j++)
	{
		if (eventList[j].getEventType()!="d")
		{
			arrayIndex=getTimeArrayIndex(eventList[j].getEndTime());
			if (arrayIndex==-1)
				timeArray[getTimeArrayIndex(eventList[j].getStartTime())]->push_back(eventList[j]);
			if(arrayIndex==0)
				arrayIndex=24;
			for(k=getTimeArrayIndex(eventList[j].getStartTime());k<arrayIndex;k++)
			{
				timeArray[k]->push_back(eventList[j]);
			}
			if(eventList[j].getEndTime().getMinutes()!=0)
				timeArray[k]->push_back(eventList[j]);
		}
		else
			hasDeadlines = true;
	}
				
	for(i=7;i<24;i++)
	{
		if(timeArray[i]->size()==0)
			end++;
					
		else
		{
			if(start!=end)
			{
				output << "You are free from " << arrayIndexToString(start) << " to " << arrayIndexToString(end) << "\n";
				start=end;
			}
			start++;
			end++;
		}
	}
	if(start!=end)
		output << "You are free from " << arrayIndexToString(start) << " to " << arrayIndexToString(end) << "\n";

	if (hasDeadlines)
	{
		output << "Please Note that you have the following Deadlines on the same day:\n";
		int count = 0;
		
		for(int j=0;j<eventList.size();j++)
		{
			if (eventList[j].getEventType()=="d")
			{
				count++;
				output << count << ". " << eventList[j].getName() << " by " <<  eventList[j].getStartTime().formatCompleteTime(eventList[j].getEndTime()) << "\n";
			}
		}
	}
	
	displayList.clear();
	return output.str();
	
}

int UpcomingHandler::getTimeArrayIndex(Time eventTime)
{
	int index;
	if(eventTime.getAmPm()=="")
	{
		return -1;
	}

	if(equalsIgnoreCase(eventTime.getAmPm(),"am"))
	{
		index=eventTime.getHour();
		if(index==12)
			index=0;
	}
	else
	{
		index=eventTime.getHour()+12;
		if(index==24)
			index=12;
	}
	return index;
}

string UpcomingHandler::arrayIndexToString(int index)
{
	Time time;
	Time tempTime;
	if(index==24)
		index=0;
	if(index<12)
	{
		if(index==0)
			time.setHour(12);
		else
			time.setHour(index);
		time.setAmPm("am");
	}
	else
	{
		if(index!=12)
			time.setHour(index-12);
		else
			time.setHour(12);
		time.setAmPm("pm");
	}
	return time.formatTime();
}


bool UpcomingHandler::checkIfClash()
{
	bool flag = false;
	Event eventObj = eventOrder.top();
	Date dateToUndo=masterList[0].dateStringToObject(eventObj.getId().substr(0,8));
	int dateIndex=masterList[0].dateDifference(dateToUndo);
	vector<Event> eventList=masterList[dateIndex].getEventList();
	Time startTime=eventObj.getStartTime();
	Time endTime=eventObj.getEndTime();

	for (int i=0; i<eventList.size(); i++)
	{
		if (endTime.getAmPm()=="")
		{
			if(eventList[i].getId()==eventObj.getId())
				continue;

			if (eventList[i].getStartTime().getHour() == startTime.getHour())
			{
				flag = true;
				break;
			}
		}
		else
		{
			if(eventList[i].getId()==eventObj.getId())
				continue;

			if (eventList[i].getStartTime().getHour() >= startTime.getHour() && eventList[i].getStartTime().getHour() < endTime.getHour())
			{
				flag = true;
				break;
			}
		}
	}
	return flag;
}

string UpcomingHandler:: undoCommand ()
{
	if (commandOrder.size()==0)
		throw TempusException(TempusException::INVALID_UNDO_EXCEPTION);
	
	string commandType=commandOrder.top();
	commandOrder.pop();
	Event eventObj=eventOrder.top();
	eventOrder.pop();

	Date dateToUndo=masterList[0].dateStringToObject(eventObj.getId().substr(0,8));
	int index = masterList[0].dateDifference(dateToUndo);
	//struct Task currentTask;
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

	else if (equalsIgnoreCase(commandType,"Delete"))
	{
		masterList[index].addEvent(eventObj.getId(),eventObj.getName(), eventObj.getLocation(), eventObj.getStartTime(), eventObj.getEndTime(), eventObj.getEventType(), eventObj.getEventStatus());
		return commandType;
	}
	else if (equalsIgnoreCase(commandType, "Edit"))
	{
		int indexToDelete=masterList[index].getIndex(eventObj.getId());
		masterList[index].deleteEvent(indexToDelete);
	
		Event eventObj2=eventOrder.top();
		eventOrder.pop();
		commandOrder.pop();
		dateToUndo=masterList[0].dateStringToObject( eventObj2.getId().substr(0,8));
		index = masterList[0].dateDifference(dateToUndo);

		masterList[index].addEvent(generateId(masterList[index]),eventObj2.getName(), eventObj2.getLocation(), eventObj2.getStartTime(), eventObj2.getEndTime(), eventObj2.getEventType(), eventObj2.getEventStatus());
		return commandType;
	}
	else if (equalsIgnoreCase(commandType, "Add"))
	{
		int indexToDelete=masterList[index].getIndex(eventObj.getId());
		masterList[index].deleteEvent(indexToDelete);
		return commandType;
	}
}

UpcomingHandler::~UpcomingHandler(void)
{
}
