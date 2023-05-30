#include <iostream>
#include <string>

using namespace std;
void selection(int leftnum, int sub);
string S[10];
bool S1[10];
int length;
int main()
{
	for (int i = 0;; i++)
	{
		string t;
		cin >> t;
		if (t != "0")
		{
			S[i] = t;
		}
		else
		{
			length = i;
			break;
		}
	}
	for (int i = 0; i < 10; i++)
		S1[i] = 0;
	cout << "{";
	for (int i = 0; i <= length; i++)
	{
		selection(i, 0);
	}
	cout << "}";


	system("pause");
}

void selection(int leftnum, int sub)
{
	if (leftnum == 0)
	{
		cout << "(";
		for (int i = 0; i < sub - 1; i++)
		{
			if (S1[i])
				cout << S[i] << ",";
		}
		if (S1[sub - 1])
			cout << S[sub - 1];
		cout << "),";

	}
	else
	{
		if ((length - sub) > leftnum)
		{
			S1[sub] = 0;
			selection(leftnum, sub + 1);
		}
		S1[sub] = 1;
		selection(leftnum - 1, sub + 1);
	}

}