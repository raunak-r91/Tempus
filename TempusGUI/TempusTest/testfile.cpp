#include "MainLogic.h"
#include "gtest/gtest.h"


// checks whether the incrementing method of the time works
//the inputs are valid and so the output should be true
TEST(testing_time_increment, time_sample)
{

	ifstream ifs("passTimeincrement.txt");
	Time timeObj, timeObj2;
	int minutes;
	string input, time1, time2;
	stringstream str;

	while(getline(ifs,input))
	{
		str<<input;
		str>>time1;
		str>>minutes;
		str>>time2;
		timeObj.timeStringToObject(time1);
		timeObj2.timeStringToObject(time2);
		timeObj.incrementTime(minutes);
		EXPECT_EQ(timeObj.isTimeEqual(timeObj2), true);
	}

}

// checks whether the incrementing method of the date works
//the inputs are valid and so the output should be true
TEST(testing_date_increment, date_sample)
{
	time_t t=time(0);
	tm* now=localtime(&t);
	Date currentDate;
	currentDate = currentDate.setDateObject(now->tm_mday,now->tm_mon+1, now->tm_year+1900);
	//Date obj;
	//obj.setDay(now->tm_mday);
	//obj.setMonth(now->tm_mon+1);
	//obj.setYear(now->tm_year + 1900);

	//MainLogic temp;
	ifstream ifs("passDateincrement.txt");
	Date dateObj, dateObj2;
	// set//temp.getCurrentSystemDate();
	int days;
	string input, date1, date2;
	stringstream str;

	while(getline(ifs,input))
	{
		str<<input;
		str>>date1;
		str>>date2;
		str>>days;
		dateObj = currentDate.dateStringToObject(date1);
		dateObj2 = currentDate.dateStringToObject(date2);
		dateObj.incrementDays(days);
		EXPECT_EQ(dateObj.dateDifference(dateObj2), 0);
	}

}

// checks the format of the date entered
//the inputs are valid and so the output should be true
TEST(testing_valid_date, date_sample)
{
	time_t t=time(0);
	tm* now=localtime(&t);
	Date currentDate;
	currentDate = currentDate.setDateObject(now->tm_mday,now->tm_mon+1, now->tm_year+1900);
	string buffer;
	//Date dateObj;
	Date testdate;
	//MainLogic temp;
	//dateObj = temp.getCurrentSystemDate();//dateObj.setDateObject(4,11,2011);
	ifstream ifs("passDateinput.txt");
	while (getline(ifs, buffer))
	{
		testdate = currentDate.dateStringToObject(buffer);
		EXPECT_EQ (currentDate.isValidDate(testdate), true);
	}
	ifs.close();
}

//checks the format of the date
//the inputs are invalid and so the output should be false
TEST(testing_invalid_date, date_sample)
{
	time_t t=time(0);
	tm* now=localtime(&t);
	Date currentDate;
	currentDate=currentDate.setDateObject(now->tm_mday,now->tm_mon+1, now->tm_year+1900);
	string buffer;
	Date dateObj;
	Date testdate;
	//dateObj = temp.getCurrentSystemDate();
	
	ifstream ifs("failDateinput.txt");
	while (getline(ifs, buffer))
	{
		testdate = currentDate.dateStringToObject(buffer);
		EXPECT_EQ (currentDate.isValidDate(testdate), false);
	}
	ifs.close();
}

//just checks the format individually of the start time and end time
//the inputs are valid and so the output should be true
TEST(testing_valid_time, time_sample)
{
	string buffer;
	Time timeObj;
	
	ifstream ifs("passTimeinput.txt");
	while (getline(ifs, buffer))
	{
		CommandParser temp;
		temp.setInputDetails(" time "+ buffer);
		timeObj.timeStringToObject(buffer);
		EXPECT_EQ (temp.getStartTimeObj().isValidTime(), true);
		
		if (temp.hasEndTime())
			EXPECT_EQ (temp.getEndTimeObj().isValidTime(), true);
		
	}
	ifs.close();
}


//just checks the format individually of the start time and end time
//the inputs are invalid and so the output should be false
TEST(testing_invalid_time, time_sample)
{
	string buffer;
	bool result;
	ifstream ifs("failTimeinput.txt");
	while (getline(ifs, buffer))
	{
		CommandParser temp;
		temp.setInputDetails(" time "+ buffer);
		result = temp.getStartTimeObj().isValidTime();
		if (result)
			result = temp.getEndTimeObj().isValidTime();
		EXPECT_EQ (result, false);
	}
	ifs.close();
}


int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
    std::getchar(); // keep console window open until Return keystroke
}