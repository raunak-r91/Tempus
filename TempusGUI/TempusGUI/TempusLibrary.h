#pragma once

#include <string>
#include <sstream>
#include <ctype.h>
#include <vector>
using namespace std;


static bool hasString(string userInput, string stringToBeSearched)
{
	int found;
	found=stringToBeSearched.find(userInput);
	if(found!=string::npos)
		return true;
	return false;
}
static bool equalsIgnoreCase(string str1, string str2){
	
	if (str1.size() != str2.size()) 
		return false;
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2){
        if (tolower(*c1) != tolower(*c2)) 
			return false;
    }
    return true;
}
static string toLower(string text)
{
	stringstream converted;
	for (int i=0; i<text.size();i++)
	{
		if (isdigit(text[i]))
			converted << text[i];
		else
			converted << (char)tolower(text[i]);
	}
	return converted.str();
}
static string trim(string text, string toTrim){
	
	string trimmedText;
	int startPos=text.find_first_not_of(toTrim);
	int endPos=text.find_last_not_of(toTrim);
	if(startPos==-1)
		trimmedText="";
	else
		trimmedText=text.substr(startPos,endPos-startPos+1);
	return trimmedText;
}
static vector<string> tokenize(string inputDate)
{
	stringstream strstr(inputDate);
	vector<string> tokenizedDate;
	string buffer;
	while(strstr >> buffer)
		tokenizedDate.push_back(buffer);
	return tokenizedDate;
}

