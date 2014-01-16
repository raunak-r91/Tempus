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
#include "stdafx.h"
#include "MainLogic.h"

ifstream filename ("testinput.txt");
ofstream logger("logfile.txt");

Date MainLogic::getCurrentSystemDate()
{
	logger << "Getting Current Date" << endl;
	time_t t=time(0);
	tm* now=localtime(&t);
	Date obj;
	obj.setDay(now->tm_mday);
	obj.setMonth(now->tm_mon+1);
	obj.setYear(now->tm_year + 1900);
	return obj;
}

MainLogic::MainLogic()
{
	upcomingObj = UpcomingHandler::getInstance();
	historyObj = HistoryHandler::getInstance();
	FileStorage inputFile;
	logger << "Reading input File" << endl;
	inputFile.readFromFile(upcomingObj, historyObj);
	upcomingObj->clearStack();
	historyObj->clearStack();
	updateDisplayList();
	updatePendingList();
}

MainLogic::~MainLogic()
{
	FileStorage outputFile;
	logger << "Writing to file" << endl;
	logger.close();
	outputFile.writeToFile(upcomingObj , historyObj);
}

string MainLogic::getSuccessMessage(CommandParser test)
{
	string inputCommand = test.getInputCommand();
	string output;
	bool flag=true;

	if(equalsIgnoreCase(inputCommand,"Add"))
		output = "The Following Event Was Added: ";
	else if(equalsIgnoreCase(inputCommand, "Delete") && dtype==UPCOMING)
		output = "The Following Event Was Deleted: ";
	else if(equalsIgnoreCase(inputCommand, "Edit"))
		output = "The Following Event Was Edited: ";
	else if(equalsIgnoreCase(inputCommand, "Done"))
	{
		if(!test.hasIndex())
		{
			output = "All Events Were Marked As Done";
			flag=false;
		}
		else
			output = "The Following Event Was Marked As Done: ";
	}
	else if(equalsIgnoreCase(inputCommand,"Undo"))
	{
		output = "The Following Command Was Undone: "+ statusMessage;
		flag=false;
	}
	else if(equalsIgnoreCase(inputCommand, "Pending"))
	{
		if (dtype==UPCOMING)
			output="You have no pending events in the past 3 days";
		flag=false;
	}
	else if(equalsIgnoreCase(inputCommand, "History"))
	{
		if (historyObj->getDisplayList().size()==0)
			output="There are no events in the archive";
		flag=false;
	}
	else
	{
		output="";
		flag=false;
	}
	
	if(flag)
		output += test.getEventDetails();
	if(equalsIgnoreCase(inputCommand,"Add")||equalsIgnoreCase(inputCommand,"Edit"))
		if(upcomingObj->checkIfClash())
			output =output + "Please Note That There Is A Clash With Another Event";
	return output;
}

void MainLogic::processCommand(string command)
{
	CommandParser test;
	bool valid=false;
	statusMessage="";

	try{
		test.setInputDetails(command);
		valid=test.isValidInput();

		if(valid)
		{
			if (dtype==PENDING)
				processPending(test);
	
			else 
				processUpcoming(test);
		}
	}
	catch ( TempusException obj)
	{
		statusMessage = obj.getMessage();
		valid=false;
	}

	if(valid)
	{
		statusMessage= getSuccessMessage(test);
		FileStorage outputFile;
		logger << "Writing to file" << endl;
		outputFile.writeToFile(upcomingObj, historyObj);
	}
}
void MainLogic::processPending(CommandParser& test)
{
	string inputCommand =test.getInputCommand();

	if (equalsIgnoreCase(inputCommand, "Add"))
		upcomingObj->addEvent(test);
	if (equalsIgnoreCase(inputCommand,"Delete"))
		throw TempusException(TempusException::INVALID_DELETE_EXCEPTION, "Cannot Delete In Archive");
	else if (equalsIgnoreCase(inputCommand, "Show"))
		showWhenPending(test);
	else if (equalsIgnoreCase(inputCommand, "Edit"))
	{
		historyObj->editEvent(test);
		upcomingObj->addEvent(test);
	}
	else if (equalsIgnoreCase(inputCommand, "Done"))
		historyObj->markAsDone(test);
	else if (equalsIgnoreCase(inputCommand, "Agenda"))
		updateDisplayList();
	else if (equalsIgnoreCase(inputCommand, "History"))
	{
		historyObj->defaultList();
		label = "                  Archive";
	}
	else if (equalsIgnoreCase(inputCommand, "Pending"))
		updatePendingList();
	else if (equalsIgnoreCase(inputCommand, "sft"))
	{
		outputDisplay=upcomingObj->showFreeTime(test);
		upcomingObj->showEvents(test);
		dtype=OTHER;
		label="    Showing Free Time For The Day";
	}
	else if (equalsIgnoreCase(inputCommand, "Undo"))
		statusMessage = undoLogic();
	pushState(inputCommand);
	
	if(!((equalsIgnoreCase(inputCommand,"Add") || equalsIgnoreCase(inputCommand, "sft") || equalsIgnoreCase(inputCommand,"Show") || equalsIgnoreCase(inputCommand,"History")) || equalsIgnoreCase(inputCommand,"Agenda")))
		updatePendingList();
	else if(equalsIgnoreCase(inputCommand, "Add"))
		updateDisplayList();
}
void MainLogic::showWhenPending(CommandParser test)
{
	dtype=UPCOMING;

	if (!test.hasWords())
		updateDisplayList();
	else if (getCurrentSystemDate().compareDates(test.getDateObj())>= 0)
	{
		upcomingObj->showEvents(test);
		label = "               Day Agenda";
		
	}
	else if (test.getInputEventType()=="d")
	{
		upcomingObj->showEvents(test);
		label = "          Showing All Deadlines";
		
	}
	else
	{
		dtype=PENDING;
		label = "                  Archive";
		historyObj->showEvents(test);
		
	}
}
void MainLogic::showWhenUpcoming(CommandParser test)
{
	if (!test.hasWords())
		updateDisplayList();
	else if (test.hasDate() && getCurrentSystemDate().compareDates(test.getDateObj()) < 0)
	{
		dtype=PENDING;
		label = "                  Archive";
		historyObj->showEvents(test);
		
	}
	else
	{
		upcomingObj->showEvents(test);
		if (getCurrentSystemDate().compareDates(test.getDateObj())>= 0)
			label = "                 Day Agenda";
		else if (test.getInputEventType()=="d")
			label = "              Showing All Deadlines";
		else
			label = "               Search Results";
	}
		
}
void MainLogic::processUpcoming(CommandParser& test)
{
	string inputCommand =test.getInputCommand();

	if (equalsIgnoreCase(inputCommand, "Add"))
		upcomingObj->addEvent(test);
	else if (equalsIgnoreCase(inputCommand, "Show"))
		showWhenUpcoming(test);
	else if (equalsIgnoreCase(inputCommand, "Edit"))
		upcomingObj->editEvent(test);
	else if (equalsIgnoreCase(inputCommand, "Done"))
		upcomingObj->markAsDone(test);
	else if (equalsIgnoreCase(inputCommand, "Agenda"))
		updateDisplayList();
	else if (equalsIgnoreCase(inputCommand, "History"))
	{
		historyObj->defaultList();
		dtype=PENDING;
		label = "                  Archive";
	}
	else if (equalsIgnoreCase(inputCommand, "Pending"))
		updatePendingList();
	else if (equalsIgnoreCase(inputCommand, "sft"))
	{
		outputDisplay=upcomingObj->showFreeTime(test);
		dtype=OTHER;
		label="    Showing Free Time For The Day";
		upcomingObj->showEvents(test);
	}
	else if (equalsIgnoreCase(inputCommand, "Delete"))
		upcomingObj->deleteEvent(test);
	else if (equalsIgnoreCase(inputCommand, "Undo"))
		statusMessage = undoLogic();
	
	pushState(inputCommand);
	if(!(equalsIgnoreCase(inputCommand,"Pending") || equalsIgnoreCase(inputCommand, "History") || equalsIgnoreCase(inputCommand, "Show") || equalsIgnoreCase(inputCommand, "sft")))
		updateDisplayList();
}

void MainLogic::pushState(string inputCommand)
{
	if (equalsIgnoreCase(inputCommand, "Add") || equalsIgnoreCase(inputCommand, "Edit") ||equalsIgnoreCase(inputCommand,"Done") || equalsIgnoreCase(inputCommand,"Delete"))
	{
		dtypeOrder.push(dtype);
		commandOrder.push(inputCommand);
	}
}
string MainLogic::undoLogic()
{
	if(commandOrder.size()==0)
		throw TempusException(TempusException::INVALID_UNDO_EXCEPTION);
	
	DISPLAYTYPE temp = dtypeOrder.top();
	string tempCommand = commandOrder.top();
	dtypeOrder.pop();
	commandOrder.pop();

	if (equalsIgnoreCase(tempCommand,"Add") || equalsIgnoreCase(tempCommand, "Delete"))
		upcomingObj->undoCommand();
	else if (equalsIgnoreCase(tempCommand, "Done"))
	{
		if (temp==PENDING)
			historyObj->undoCommand();
		else if (temp==UPCOMING)
			upcomingObj->undoCommand();
	}
	else if (equalsIgnoreCase(tempCommand, "Edit"))
	{
		if(temp==PENDING)
		{
			historyObj->undoCommand();
			upcomingObj->undoCommand();
		}
		else if(temp==UPCOMING)
			upcomingObj->undoCommand();
	}
	return tempCommand;
}
void MainLogic::updateDisplayList()
{
	logger << "Updating Display List" << endl;
	upcomingObj->defaultList();
	dtype=UPCOMING;
	label = "                  Agenda";
}
void MainLogic::updatePendingList()
{
	logger << "Updating Pending List" << endl;
	historyObj->showPending();
	if (historyObj->getDisplayList().size()==0)
		updateDisplayList();
	else
	{
		dtype = PENDING;
		label = "       Pending Events (Past 3 Days)";
	}
}
string MainLogic::displayOutput()
{
	logger << "Formatting Display output" << endl;
	
	stringstream output;
	if(dtype==UPCOMING)
		output << upcomingObj->formatDisplayList();
	else if (dtype ==PENDING)
		output << historyObj->formatDisplayList();
	else
	{
		output << upcomingObj->formatDisplayList() << endl << outputDisplay;
		outputDisplay="";
	}
	return output.str();
}
string MainLogic::getStatusMessage()
{
	return statusMessage;
}

bool MainLogic::checkIfReminder()
{
	Time obj=getCurrentSystemTime();
	obj.incrementTime(10);
	int flag=-1;
	int index=0;
	
	if (obj.getHour()==12 && obj.getAmPm()=="am" && obj.getMinutes() <10)
		index=1;
	if (upcomingObj->getMasterList().size()<= index)
		return false;

	for (int  i=0; i<upcomingObj->getMasterList().at(index).getEventListLength(); i++)
	{
		if (obj.isTimeEqual(upcomingObj->getMasterList().at(index).getEvent(i).getStartTime() ))
			return true;
	}
	return false;
}
string MainLogic::getReminderText()
{
	stringstream outputstr;
	string text="";
	Time obj=getCurrentSystemTime();
	obj.incrementTime(10);
	int count=1;
	outputstr << "Please note, you have the following events scheduled after 10 minutes\n";
	int index =0;

	if (obj.getHour()==12 && obj.getAmPm()=="am" && obj.getMinutes() <10)
		index =1;
	
	for (int  i=0; i<upcomingObj->getMasterList().at(index).getEventListLength(); i++)
	{
		if (obj.isTimeEqual(upcomingObj->getMasterList().at(index).getEvent(i).getStartTime() ))
		{
			text=upcomingObj->getMasterList().at(index).getEvent(i).getEventDetails();
			outputstr << count << ". " << text.substr(0,text.size()-3) << "\n";
			count++;
		}
	}
	return outputstr.str();
}

Time MainLogic::getCurrentSystemTime()
{
	time_t t=time(0);
	tm* now=localtime(&t);
	int tempTime = now->tm_hour;
	int tempMins = now->tm_min;
	
	Time obj;
	
	if (tempTime>=12)
		obj.setAmPm("pm");
	else if (tempTime < 12)
		obj.setAmPm("am");
	
	if (tempTime>12)
		obj.setHour(tempTime-12);
	else if(tempTime==0)
		obj.setHour(12);
	else if(tempTime<=12)
		obj.setHour(tempTime);
	
	
	obj.setMinutes(tempMins);
	return obj;
}
bool MainLogic::readIfNextday ()
{
	time_t t=time(0);
	tm* now=localtime(&t);
		
	if (now->tm_hour ==0 && now->tm_min ==0 && now->tm_sec==1)
	{
		FileStorage inputFile;
		inputFile.readFromFile(upcomingObj, historyObj);
		upcomingObj->clearStack();
		historyObj->clearStack();
		updateDisplayList();
		return true;
	}
	return false;
}

string MainLogic:: getLabel()
{
	return label;
}