# include <iostream>
# include <iomanip>
# include "Time.h"

using namespace std;

Time::Time(int a, int b, int c)
{
	setTime(a, b, c);
}
Time & Time::setTime(int a, int b, int c)
{
	setHour(a);
	setMinute(b);
	setSecond(c);
	return *this;
}
Time & Time::setHour(int h)
{
	totalSeconds = h * 3600 + getMinute() * 60 + getSecond();
	return *this;
}
Time &Time::setMinute(int m)
{
	totalSeconds = getHour() * 3600 + m * 60 + getSecond();
	return *this;
}
Time &Time::setSecond(int s)
{
	totalSeconds = getHour() * 3600 + getMinute() * 60 + s;
	return *this;
}
int Time::getHour() const
{
	int h = totalSeconds / 3600;
	return h;
}
int Time::getMinute() const
{
	int m = (totalSeconds % 3600) / 60;
	return m;
}
int Time::getSecond() const
{
	int s = totalSeconds % 60;
	return s;
}
void Time::printUniversal() const
{
	cout << setfill('0') << setw(2) << getHour() << ":" << setw(2) << getMinute() << ":" << setw(2) << getSecond() << endl;
}
void Time::printStandard() const
{
	cout << ((getHour() == 12) ? 12 : getHour() % 12)
		<< ":" << setfill('0') << setw(2) << getMinute() << ":" << setw(2) << getSecond() << (getHour()< 12 ? "AM" : "PM") << endl;
}

