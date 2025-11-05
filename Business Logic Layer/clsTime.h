#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include<string>
using namespace std;
class clsTime
{
	short _Hour;
	short _Minute;
	short _Second;
public :
	clsTime()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Hour = now->tm_hour;
		_Minute = now->tm_min;
		_Second = now->tm_sec;

	}

	static string TimeToString(clsTime Time)
	{
		return  to_string(Time._Hour) + ":" + to_string(Time._Minute) + ":" + to_string(Time._Second);
	}
};

