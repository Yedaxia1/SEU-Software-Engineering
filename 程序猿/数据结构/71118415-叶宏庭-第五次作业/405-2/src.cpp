#include <iostream>
#include <string>
#include <stack>

using namespace std;

template<class T>
void QuickSort(T* a, const int left, const int right);
int counter = 0;

int main()
{
	int a[] = {-1,1,2,3,4,5,6,7,8,9,10};
	QuickSort(a, 1, 10);
	cout << "The sequence(sorted) is:";
	for (int i = 1; i < 11; i++)
		cout << a[i] << " ";
	cout << endl;
	cout << "The length is:" << 10 << endl;
	cout << "n*n=" << 10 * 10 << endl;
	cout << "The sort time is:" << counter << endl;
	cout << endl;

	int b[] = { -1,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	QuickSort(b, 1, 14);
	cout << "The sequence(sorted) is:";
	for (int i = 1; i < 15; i++)
		cout << b[i] << " ";
	cout << endl;
	cout << "The length is:" << 14 << endl;
	cout << "n*n=" << 14 * 14 << endl;
	cout << "The sort time is:" << counter << endl;
	cout << endl;

	int c[] = { -1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	QuickSort(c, 1, 16);
	cout << "The sequence(sorted) is:";
	for (int i = 1; i < 17; i++)
		cout << c[i] << " ";
	cout << endl;
	cout << "The length is:" << 16 << endl;
	cout << "n*n=" << 16 * 16 << endl;
	cout << "The sort time is:" << counter << endl;
	return 0;


}

template<class T>
void QuickSort(T* a,const int left,const int right)
{
	if (left < right)
	{
		int i = left,
			j = right + 1,
			pivot = a[left];
		do {
			do { i++; counter++; } while (a[i] < pivot);
			do { j--; counter++; } while (a[j] > pivot);
			if (i < j)swap(a[i], a[j]);
		} while (i < j);
		swap(a[left], a[j]);

		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right);

	}
}