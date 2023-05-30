#include <iostream>

#include <string>

using namespace std;

int main()
{
	cout << "Enter two numbers for sizeof a and b." << endl;
	int n=0,m=0;
	cin >> n>> m; //输入n，m
	int result=1;
	int *a = new int[n];
	int *b = new int[m];
	cout << "Enter elements to a and b" << endl;
	for (int i = 0; i < n; i++)//输入a
		cin >> a[i];
	for (int i = 0; i < m; i++)//输入b
		cin >> b[i];
	int min = (n <= m ? n : m);//获取n，m的较小数
	for (int i = 0; i < min; i++)
	{//循环次数为较小数，防止越界
		if (a[i] == b[i])
		{
			if (i == n - 1 && n < m)//若a整个数组与b的一部分相等，则a<b,result用-1表示
			{
				result = -1;
				break;
			}
			else if (i == n - 1 && n == m)//若a整个数组与b完全相等，则a=b，result用0表示
			{
				result = 0;
				break;
			}
			continue;
		}
		else if (a[i] < b[i] && i != 0)//若出现a[i]<b[i]，且不是第一个，则a<b，result用-1表示
		{
			result = -1;
			break;
		}
	}
	cout << "The result of a and b is:";
	if (result == -1)
		cout << "a<b";
	else if (result == 0) cout << "a==b";
	else cout << "a>b";
		
	system("pause");
}
