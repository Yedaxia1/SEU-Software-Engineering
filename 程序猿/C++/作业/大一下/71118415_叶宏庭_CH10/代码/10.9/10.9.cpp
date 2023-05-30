# include <iostream>
# include "Time.h"

using namespace std;

int main()
{
	Time t;

	t.setTime(20, 12, 32);

	t.printUniversal();
	t.printStandard();

	t.setHour(10).setMinute(23).setSecond(5);

	t.printUniversal();
	t.printStandard();

	return 0;
}