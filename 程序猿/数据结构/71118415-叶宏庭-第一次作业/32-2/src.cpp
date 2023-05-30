#include <iostream>
#include <string>
void selection(int, int, int);

using namespace std;

bool values[100];

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		values[i] = 0;
	}

	for (int i = 0; i <= n; i++)
	{
		selection(i, n, 0);
	}

	system("pause");
}
void selection(int leftnum, int length, int sub)
{
	if (leftnum == 0)
	{
		for (int i = sub; i < length; i++)
		{
			values[i] = 0;
		}
		for (int i = 0; i < length; i++)
		{
			if (values[i])
				cout << "true ";
			else
				cout << "false ";
		}
		cout << endl;
	}
	else
	{
		values[sub] = 1;
		selection(leftnum - 1, length, sub + 1);
		if ((length - sub) > leftnum)
		{
			values[sub] = 0;
			selection(leftnum, length, sub + 1);
		}
	}
}