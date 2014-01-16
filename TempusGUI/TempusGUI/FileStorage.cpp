/*
Authors : Winnie Har
FileStorage does the following:
--Contains the methods to read from and write into the external storage file.
--The method to read the external file is called by MainLogic during the startup of the program, and when the current day changes (i.e. The current time crosses from 11.59pm to 12.01am).
--The method to write to the external file is called when the user exits the program, and every time the user enters a successful command.
*/
#include "stdafx.h"
#include "FileStorage.h"

FileStorage :: FileStorage()
{}

void FileStorage :: readFromFile(ListHandler* upcomingObj, ListHandler* historyObj)
{
	Date currentDate=upcomingObj->getCurrentDate();
	int index;
	stringstream str;
	vector<string> storedDetails;
	ifstream textFile("Tempus.txt");
	string temp = "";

	textFile.seekg(0, ios::end);//puts the cursor in the file to the end
	int length = textFile.tellg(); // detects the number of characters until the end of the file
 
	if(length!=0 && textFile.is_open())
    {
		textFile.seekg(0, ios::beg);//places the cursor back to the beginning of the file
		while(!textFile.eof())
		{		
			CommandParser test;
			for (int i=0; i<7; i++)
			{
				getline(textFile,temp);
				storedDetails.push_back(temp);
			}
			stringstream input;
			test.setId(storedDetails[0]);
			input << storedDetails.at(1); //name
			input << " Date " << storedDetails[0].substr(0,8); //date
			if (storedDetails[4] == "d")
				input << " By " << storedDetails[2];
			else
				input << " Time " << storedDetails[2];//time
			if (storedDetails[3] !="undefined")
				input << " Location " << storedDetails[3];//location
			
			test.setStatus(storedDetails.at(5));

			storedDetails.clear();
			
			test.setInputDetails(input.str());

			Date newDate=currentDate.dateStringToObject(test.getInputDate());
			if(currentDate.compareDates(newDate)>=0)
				upcomingObj->addEvent(test);
			else
				historyObj->addEvent(test);
		}
	}
	textFile.close();
}

void FileStorage :: writeToFile(ListHandler* upcomingObj, ListHandler* historyObj)
{
	ofstream textFile("Tempus.txt");
	string historyToWrite, currentToWrite;
	historyToWrite = transferText(historyObj->getMasterList() ,"history"); 
	historyToWrite=trim(historyToWrite, "\n");
	currentToWrite = transferText(upcomingObj->getMasterList() ,"current"); 
	currentToWrite=trim(currentToWrite, "\n");
	textFile << historyToWrite;//write in the text of history

	if (historyToWrite!="" && currentToWrite!="")
		textFile << endl << endl;
	
	textFile << currentToWrite;//write in the text of currentList
	textFile.close();
}

string FileStorage::transferText(vector<Date> list, string type)
{
	stringstream allInfo;
	Event currentEvent;
	int index=0;
	assert (type=="history" || type=="current");

	for (int i=0; i <list.size(); i++)
	{
		if (type=="history")// checks if the list type is history, then changes to index to size-i-1
		{
			index = list.size()-1-i;
		}
		else
			index = i;

		for (int j=0; j < list[index].getEventListLength(); j++)
		{
			currentEvent = list[index].getEvent(j);

			allInfo << currentEvent.getId() << endl;
			allInfo << currentEvent.getName() << endl;
			allInfo << currentEvent.getStartTime().formatTime();
			if(currentEvent.getEndTime().getAmPm()!="")
				allInfo << "-" << currentEvent.getEndTime().formatTime();
			allInfo << endl;
		
			if (currentEvent.getLocation()=="") //if the location is not specified, then write undefined
					allInfo << "undefined\n";
			else
				allInfo << currentEvent.getLocation() << endl;

			allInfo << currentEvent.getEventType() << endl;
			allInfo << currentEvent.getEventStatus() << endl;
			allInfo << endl;
		}
    }

	return allInfo.str();
}
