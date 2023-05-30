#include <iostream>
#include <string>
using namespace std;

class String {
public:
	String(char *a, int m)
	{
		length = m;
		s = new char[length];
		for (int i = 0; i < length; i++)
			s[i] = a[i];
		f = new int[length];
		fill(f, f, 0);
	}
	String(string a)
	{
		length = a.length();
		s = new char[length];
		for (int i = 0; i < length; i++)
			s[i] = a[i];
		f = new int[length];
		fill(f, f, 0);
	}
	int Frequency(char c)
	{
		int counter = 0;
		for (int i = 0; i < length; i++)//遍历数组，查找次数
		{
			if (s[i] == c)
				counter++;
		}
		return counter;
	}
private:
	char *s;
	int length;
	int *f;
};

int main()
{
	string str;
	cout << "Enter a string."<<endl;
	cin >> str;
	String a(str);
	char c;
	cout << "Enter the char you want to find." << endl;
	cin >> c;
	cout << "The frequency of " << c << " is :" << a.Frequency(c) << endl;
	system("pause");
}
