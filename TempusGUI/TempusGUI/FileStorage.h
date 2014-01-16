/*

Authors : Winnie Har
FileStorage does the following:
--Contains the methods to read from and write into the external storage file.
--The method to read the external file is called by MainLogic during the startup of the program, and when the current day changes (i.e. The current time crosses from 11.59pm to 12.01am).
--The method to write to the external file is called when the user exits the program, and every time the user enters a successful command.
*/
#ifndef _FILE_STORAGE_H_
#define _FILE_STORAGE_H_

#include "Date.h"
#include "ListHandler.h"
#include "UpcomingHandler.h"
#include "HistoryHandler.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>


using namespace std;

class FileStorage
{
public:
	FileStorage();
	void readFromFile(ListHandler* upcomingObj, ListHandler* historyObj);
	void writeToFile(ListHandler* upcomingObj, ListHandler* historyObj);
private:
	string transferText(vector<Date> list, string);
};
#endif