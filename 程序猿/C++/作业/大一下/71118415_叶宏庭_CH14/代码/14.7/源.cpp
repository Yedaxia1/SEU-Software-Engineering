# include <iostream>
# include "Array.h"

using namespace std;

int main()
{
	Array<int> arrayInt(10);
	Array<double> arrayDouble(10);
	Array<char> arrayChar(10);

	for (int i = 0; i < 10; i++)
	{
		arrayInt[i] = i;
		arrayDouble[i] = (double)i;
		arrayChar[i] = (char)(i + 65);
	}

	cout << arrayInt;
	cout << setprecision(2) << fixed << arrayDouble;
	cout << arrayChar;

	system("pause");
	return 0;
}