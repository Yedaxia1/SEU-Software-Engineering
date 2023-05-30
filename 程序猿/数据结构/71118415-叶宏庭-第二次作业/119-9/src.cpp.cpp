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
		fill(f, f + length, 0);
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
			if (*(s + j) == *(s + i + 1))//����ǰ�ַ�����ǰ���ַ�����ͬ����f[j]=ǰ���f+1.
				f[j] = i + 1;
			else  f[j] = -1;
		}
		int max = -2;
		int sub = 0;
		for (int i = 0; i < lengthP; i++)
		{
			if (f[i] > max)
			{
				f[sub] = -1;
				sub = i;
				max = f[i];
			}
			else
				f[i] = -1;
		}
	}
	void getFailureFunction()
	{
		for (int i = 0; i < length; i++)
			cout << f[i] << " ";
		cout << endl;
	}
	int FastFind(String pat)//K-M-P�㷨
	{
		int posP = 0, posS = 0;
		int lengthP = pat.length, lengthS = length;
		while ((posP < lengthP) && (posS < lengthS))
		{
			if (pat.s[posP] == s[posS])//�ַ���ͬ���������ַ���������
			{
				posP++;
				posS++;
			}
			else
			{
				if (posP == 0)//��posPָ��0�������s
					posS++;
				else
					posP = pat.f[posP - 1] + 1;//posP��ָ��0����posP = pat.f[posP - 1] + 1
			}
		}
		if (posP < lengthP) return -1;//�����posP��lengthP���򲻴��ڡ�
		else return posS - lengthP;
	}
private:
	char *s;
	int length;
	int *f;
};

int main()
{
	string str;
	cout << "Enter a string." << endl;
	cin >> str;
	String a(str);
	a.FailureFunction();
	string str2;
	cout << "Enter another string." << endl;
	cin >> str2;
	String b(str2);
	b.FailureFunction();
	if (a.FastFind(b) == -1)
		cout << "b not exsit in a" << endl;
	else
		cout << "b exsit in a "<<endl;
	system("pause");
}
