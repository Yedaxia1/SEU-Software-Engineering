#include <iostream>
#include <string>
#include <stack>

using namespace std;

template<class T>
void Merge(T* initList, T* mergedList, const int l, const int m, const int n);

template<class T>
void MergePass(T* initList, T* resultList, const int n, const int s);

template<class T>
void MergeSort(T*a, const int n);

int main()
{
	int a[] = {-1,12,2,16,30,8,28,4,10,20,6,18};
	MergeSort(a, 11);
	cout << "The sequence(sorted) is:";
	for (int i = 1; i < 12; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;


}

template<class T>
void Merge(T* initList,T* mergedList,const int l,const int m,const int n)
{
	int i1, i2;
	int iResult;
	for (i1 = l, iResult = l, i2 = m + 1;
		i1 <= m && i2 <= n;
		iResult++)
	{
		if (initList[i1] <= initList[i2])
		{
			mergedList[iResult] = initList[i1];
			i1++;
		}
		else
		{
			mergedList[iResult] = initList[i2];
			i2++;
		}
	}
	copy(initList + i1, initList + m + 1, mergedList + iResult);
	copy(initList + i2, initList + n + 1, mergedList + iResult);
}

template<class T>
void MergePass(T* initList,T* resultList,const int n,const int s)
{
	int i;
	for (i = 1; i <= n - 2 * s - 1; i += 2 * s)
	{
		Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
	}
	if ((i + s - 1) < n) Merge(initList, resultList, i, i + s - 1, n);
	else copy(initList+i, initList + n + 1, resultList + i);
}

template<class T>
void MergeSort(T*a,const int n)
{
	T* tempList = new T[n + 1];
	for (int l = 1; l < n; l *= 2)
	{
		MergePass(a, tempList, n, l);
		l *= 2;
		MergePass(tempList, a, n, l);
		cout << "The sequence is:";
		for (int i = 1; i < 12; i++)
			cout << a[i] << " ";
		cout << endl;
	}
}