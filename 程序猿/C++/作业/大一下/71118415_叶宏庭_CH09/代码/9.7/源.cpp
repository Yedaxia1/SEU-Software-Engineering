# include <iostream>
# include "Time.h"
using namespace std;

int main()
{
	Time time1(15, 28, 56);
	for (int i = 0; i < 5; i++)
	{
		time1.tick();
		time1.printStandard();
	}
	cout << "\n\n";
	Time time2(15, 59, 56);
	for (int i = 0; i < 5; i++)
	{
		time2.tick();
		time2.printStandard();
	}
	cout << "\n\n";
	Time time3(23, 59, 56);
	for (int i = 0; i < 5; i++)
	{
		time3.tick();
		time3.printStandard();
	}
	return 0;
}
