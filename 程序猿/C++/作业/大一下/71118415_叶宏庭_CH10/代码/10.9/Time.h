# include <iostream>

class Time
{
public:
	Time(int = 0, int = 0, int = 0);

	//set functions
	Time &setTime(int, int, int);
	Time &setHour(int);
	Time &setMinute(int);
	Time &setSecond(int);

	// get functions
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	//print functions
	void printUniversal() const;
	void printStandard() const;
private:
	int totalSeconds;
};
