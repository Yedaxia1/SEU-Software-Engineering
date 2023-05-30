#include <iostream>
#include <string>
#include <stack>

using namespace std;

template<class T>
void Insert(const T& e, T a[], int i);

template<class T>
void InsertionSort(T a[], const int n);

int main()
{
	int a[] = {-1,12,2,16,30,8,28,4,10,20,6,18};
	cout << "Initial sequence:";
	for (int i = 1; i < 12; i++)
		cout << a[i] << " ";
	cout << endl;
	InsertionSort(a, 11);
	return 0;
}

template<class T>
void Insert(const T& e, T a[], int i)
{
	a[0] = e;
	while (e < a[i])
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

template<class T>
void InsertionSort(T a[], const int n)
{
	for (int j = 2; j <= n; j++)
	{
		T temp = a[j];
		Insert(temp,a,j-1);
		cout << "Sort " << j - 1 << "times: ";
		int i = 1;
		for (; i <= n; i++)
			cout << a[i] << " ";
		cout << endl;
	}
}