# ifndef Date_h
# define Date_h

# include <iostream>
using namespace std;

class Date
{
	friend ostream &operator<<(ostream &, const Date &);
public:
	Date(int m = 1, int d = 1, int y = 1990);
	void setDate(int, int, int);
	Date &operator++();
	Date operator++(int);
	const Date &operator+=(int);
	static bool leapYear(int);
	bool endOfMonth(int) const;
	int getMonth() const;
private:
	int month;
	int day;
	int year;

	static const int days[];
	void helpIncrement();
};
# endif