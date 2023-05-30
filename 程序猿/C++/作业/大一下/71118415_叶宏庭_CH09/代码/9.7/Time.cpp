# include <iostream>
# include <iomanip>
# include <stdexcept>
# include "Time.h"
using namespace std;

Time::Time(int hour, int minute, int second)
{
	setTime(hour, minute, second);
}
void Time::setTime(int h, int m, int s)
{
	setHour(h);
	setMinute(m);
	setSecond(s);
}
void Time::setHour(int h)
{
	if (h == 24)
	{
		h = 0;
	}
	if (h >= 0 && h < 24)
		hour = h;
	else
		throw invalid_argument("hour must be 0~23");
}
void Time::setMinute(int m)
{
	if (m == 60)
	{
		m = 0;
		Time::setHour(hour + 1);
	}
	if (m >= 0 && m < 60)
		minute = m;
	else
		throw invalid_argument("minute must be 0~59");
}
void Time::setSecond(int s)
{
	if (s == 60)
	{
		s = 0;
		Time::setMinute(minute + 1);
	}
	if (s >= 0 && s < 60)
		second = s;
	else
		throw invalid_argument("second must be 0~59");
}
int Time::getHour()
{
	return hour;
}
int Time::getMinute()
{
	return minute;
}
int Time::getSecond()
{
	return second;
}
void Time::printUnversal()
{
	cout << setfill('0') << setw(2) << getHour() << ":" << setw(2) << getMinute() << ":" << setw(2) << getSecond() << endl;
}
void Time::printStandard()
{
	cout << ((getHour() == 12) ? 12 : getHour() % 12)
		<< ":" << setfill('0') << setw(2) << getMinute() << ":" << setw(2) << getSecond() << (hour < 12 ? "AM" : "PM") << endl;
}
void Time::tick()
{
	Time::setSecond(second + 1);
}
