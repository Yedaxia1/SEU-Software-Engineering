#include <iostream>

#include <string>

using namespace std;

int main()
{
	cout << "Enter two numbers for sizeof a and b." << endl;
	int n=0,m=0;
	cin >> n>> m; //����n��m
	int result=1;
	int *a = new int[n];
	int *b = new int[m];
	cout << "Enter elements to a and b" << endl;
	for (int i = 0; i < n; i++)//����a
		cin >> a[i];
	for (int i = 0; i < m; i++)//����b
		cin >> b[i];
	int min = (n <= m ? n : m);//��ȡn��m�Ľ�С��
	for (int i = 0; i < min; i++)
	{//ѭ������Ϊ��С������ֹԽ��
		if (a[i] == b[i])
		{
			if (i == n - 1 && n < m)//��a����������b��һ������ȣ���a<b,result��-1��ʾ
			{
				result = -1;
				break;
			}
			else if (i == n - 1 && n == m)//��a����������b��ȫ��ȣ���a=b��result��0��ʾ
			{
				result = 0;
				break;
			}
			continue;
		}
		else if (a[i] < b[i] && i != 0)//������a[i]<b[i]���Ҳ��ǵ�һ������a<b��result��-1��ʾ
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
