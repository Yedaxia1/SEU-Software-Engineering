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
		fill(f, f + length, 0);
	}
	String(string a)
	{
		length = a.length();
		s = new char[length];
		for (int i = 0; i < length; i++)
			s[i] = a[i];
		f = new int[length];
		fill(f, f+length, 0);
	}
	int Frequency(char c)
	{
		int counter = 0;
		for (int i = 0; i < length; i++)
		{
			if (s[i] == c)
				counter++;
		}
		return counter;
	}
	void FailureFunction()
	{
		int lengthP = length;
		f[0] = -1;
		for (int j = 1; j < lengthP; j++)
		{
			int i = f[j - 1];
			while ((*(s + j) != *(s + i + 1)) && (i >= 0)) i = f[i];
			if (*(s + j) == *(s + i + 1))//若当前字符串跟前端字符串相同，则f[j]=前面的f+1.
				f[j] = i + 1;
			else  f[j] = -1;
		}
	}
	void getFailureFunction()
	{
		for (int i = 0; i < length; i++)
			cout << f[i] << " ";
		cout << endl;
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
	a.FailureFunction();
	a.getFailureFunction();
	system("pause");
}
