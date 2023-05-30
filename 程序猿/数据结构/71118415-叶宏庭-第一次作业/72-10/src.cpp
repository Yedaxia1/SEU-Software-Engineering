#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void initialiation(int a[]);//用于初始化数组
int BinarySearch(int*, const int, const int);
int counter; //用于计数

int main()
{
	fstream file("data.txt"); // 用于输出表格
	file << "n,times" << endl;

	//测试数组
	int a[10];
	int b[20];
	int c[50];
	int d[70];
	int e[100];
	initialiation(a);
	initialiation(b);
	initialiation(c);
	initialiation(d);
	initialiation(e);

	int x;//需要查找的数

	for (;;)
	{
		cin >> x;
		if (x != -1)//-1停止
		{
			BinarySearch(a, x, 10);
			file << 10 << "," << counter<<endl;
			BinarySearch(b, x, 20);
			file << 20 << "," << counter << endl;
			BinarySearch(c, x, 50);
			file << 50 << "," << counter << endl;
			BinarySearch(d, x, 70);
			file << 70 << "," << counter << endl;
			BinarySearch(e, x, 100);
			file << 100 << "," << counter << endl;
		}
	}
	system("pause");
}

//Program 1.10
int BinarySearch(int *a, const int x, const int n)
{//Search the sorted array a[0],...,a[n-1] for x.
	int left = 0, right = n - 1;

	counter = 0;//初始化计数为0.

	while (left <= right)
	{//there are more elements
		int middle = (left + right) / 2;
		if (x < a[middle])
		{
			right = middle - 1;
			counter++;
		}
		else if (x > a[middle])
		{
			left = middle + 1;
			counter++;
		}
		else return middle;
	}//end of while.

	return -1; //not found.
}

void initialiation(int a[])
{
	a[0] = 0;
	for (int i = 1; i < sizeof(a); i++)
		a[i] = a[i - 1] + 1;
}