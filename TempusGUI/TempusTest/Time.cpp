/*

Authors : Winnie Har
Time does the following:
--Contains all the information about a specific time (hour, minutes, am/pm)
--Contains certain helper functions used by other classes in the upper layer(such as to format the time, get the time in a string form, check whether one time is greater than the other, increment time)
*/
#include "Time.h"


Time::Time(void)
{
	hour=0;
	minutes=0;
	am_pm="";
}
Time::Time(int hour, int minutes, string am_pm)
{
	hour = hour;
	minutes = minutes;
	am_pm = am_pm;
}

void Time::setAmPm(string am_pm)
{
	this->am_pm=am_pm;
}
string Time::getAmPm()
{
	return am_pm;
}
void Time::setHour(int hour)
{
	this->hour=hour;
}
int Time::getHour()
{
	return hour;
}
void Time::setMinutes(int minutes)
{
	this->minutes=minutes;
}
int Time::getMinutes()
{
	return minutes;
}

bool Time::isGreaterThan(Time time2)
{
	bool flag;
	int temphour1=0,temphour2=0;
	if(this->am_pm=="am" && time2.am_pm=="pm")
		flag=false;
	else if(this->am_pm=="pm" && time2.am_pm=="am")
		flag=true;
	else
	{
		if(this->hour==12)
			temphour1=0;
		else 
			temphour1=this->hour;
		
		if(time2.hour==12)
			temphour2=0;
		else 
			temphour2=time2.hour;
		
		if( temphour1 > temphour2)
			flag=true;
		else if(temphour1 < temphour2)
			flag=false;
		else if(this->minutes > time2.minutes)
			flag=true;
		else if(this->minutes <= time2.minutes)
			flag=false;
	}

	return flag;

}

string Time::formatTime()
{
	int hour=getHour(), min= getMinutes();
	string am_pm=getAmPm();
	stringstream result;
	
	result << hour;
	if (min!=0)
	{
		result << ".";
	
		if (min<10)
			result <<'0';
		result << min;
	}
	result << toLower(am_pm);
	
	return result.str();
}

string Time::formatCompleteTime(Time timeObj)
{
	
	string formattedTime =formatTime();
	if (timeObj.getAmPm()!="")
	{
		formattedTime+=" to ";
		formattedTime+=timeObj.formatTime();
	}
	return formattedTime;
}

void Time::timeStringToObject(string timeString)
{
	vector<string> tokenizedTime=tokenizeTime(timeString);

	if(tokenizedTime.size()==2) //eg 7pm, 8am etc
	{
		if(hasAmPm(tokenizedTime)==1)
		{
			int hour=atoi(tokenizedTime[0].c_str());
			string am_pm=tokenizedTime[1];

			setHour(hour);
			setAmPm(am_pm);
		}
	}
	
	else if(tokenizedTime.size()==3) //eg 7.30pm, 8:15 am etc
	{
		if(hasAmPm(tokenizedTime)==2)
		{
			int hour=atoi(tokenizedTime[0].c_str());
			int minutes=atoi(tokenizedTime[1].c_str());
			string am_pm=tokenizedTime[2];

			setHour(hour);
			setMinutes(minutes);
			setAmPm(am_pm);
		}
	}
}


bool Time::isValidTime()
{
	bool flag=true;
	if(getHour()<1 || getHour()>12)
		flag=false;
	if(getMinutes()<0 || getMinutes()>59)
		flag=false;
	if(!(equalsIgnoreCase(getAmPm(),"am") || equalsIgnoreCase(getAmPm(),"pm")))
		flag=false;
	return flag;
}


int Time::hasAmPm(vector<string> tokenizedTime)
{
	for(int i=0;i<tokenizedTime.size();i++)
	{
		if(equalsIgnoreCase(tokenizedTime[i],"am") || equalsIgnoreCase(tokenizedTime[i],"pm"))
			return i;
	}
	return -1;
}


vector<string> Time::tokenizeTime(string timeToTokenize)
{
	vector<string> tokenizedTime;
	char *pch, *str;
	str = new char [timeToTokenize.size()+1];
	strcpy(str, timeToTokenize.c_str());
	string tempTime;

	pch = strtok(str,":. ");
	while(pch!=NULL)
	{
		tempTime=pch;
		if(tempTime.size()>2)
		{
			int index=findAmPm(tempTime);
			if(index!=-1)
			{
				tokenizedTime.push_back(tempTime.substr(0,index));
				tokenizedTime.push_back(tempTime.substr(index,2));
			}
			else
				tokenizedTime.push_back(tempTime);
		}
		else
			tokenizedTime.push_back(tempTime);
		pch=strtok(NULL,":. ");
	}
	return tokenizedTime;
}


int Time::findAmPm(string timeToBeTested)
{
	timeToBeTested=toLower(timeToBeTested);
	int pos=timeToBeTested.find("am");
	int pos2=timeToBeTested.find("pm");
	
	if(pos>-1)
		return pos;
	else if (pos2>-1)
		return pos2;
	return -1;
}


int Time::findHyphen(string timeToBeTested)
{
	int pos=timeToBeTested.find('-');
	if(pos>-1)
		return pos;
	return -1;
}

void Time::incrementTime(int mins)
{
	assert(mins>=0);
	for(int i=1;i<=mins;i++)
	{
		minutes++;
		if (minutes==60)
		{
			hour++;
			if(hour==12)
			{
				if (am_pm=="am")
					am_pm="pm";
	
				else 
				{
					am_pm="am";
					hour=0;
				}
			}
			minutes = 0;
		}
	}
	return;
}

bool Time::isTimeEqual(Time timeObj)
{
	if (am_pm==timeObj.getAmPm())
	{
		if (minutes ==timeObj.getMinutes() && hour==timeObj.getHour())
			return true;
	}
	return false;
}


Time::~Time(void)
{
}