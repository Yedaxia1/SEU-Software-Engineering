#ifndef Time_h
#define Time_h

class Time {
public:
	Time(int = 0, int = 0, int = 0);     //default constructor

	//set functions
	void setTime(int, int, int);
	void setHour(int);
	void setMinute(int);
	void setSecond(int);

	//get functions
	int getHour();
	int getMinute();
	int getSecond();

	void printUnversal();
	void printStandard();

	void tick();
private:
	int hour;
	int minute;
	int second;

};

#endif
