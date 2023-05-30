# include <iostream>
# include "IntegerSet.h"

using namespace std;

IntegerSet::IntegerSet()
	:set(size)
{
	for (int i = 0; i < sizeof(set); i++)
		set[i] = 0;
}
IntegerSet::IntegerSet(int *a, int l)
	:set(size)
{
	for (int i = 0; i < l; i++)
	{
		if (a[i] >= 0 && a[i] <= 100)
			set[a[i]] = true;
	}
}
IntegerSet IntegerSet::unionOfSets(IntegerSet a)
{
	IntegerSet c;
	for (int i = 0; i <= 100; i++)
	{
		if (this->set[i] || a.set[i])
			c.set[i] = true;
		else
			c.set[i] = false;
	}
	return c;
}
IntegerSet IntegerSet::intersectionOfSets(IntegerSet a)
{
	IntegerSet c;
	for (int i = 0; i <= 100; i++)
	{
		if (this->set[i] && a.set[i])
			c.set[i] = true;
		else
			c.set[i] = false;
	}
	return c;
}
void IntegerSet::insertElement(int k)
{
	set[k] = true;
}
void IntegerSet::deleteElement(int k)
{
	set[k] = false;
}
void IntegerSet::printSet()
{
	bool k = 0;
	cout << "{";
	for (int i = 0; i <= 100; i++)
		if (set[i])
		{
			cout << i<<" ";
			k = 1;
		}
	if (!k)
		cout << "---";
	cout << "}";
	cout << endl;
}
bool IntegerSet::isEqualTo(IntegerSet a)
{
	for (int i = 0; i <= 100; i++)
	{
		if (this->set[i] != a.set[i])
			return false;
	}
	return true;
}
