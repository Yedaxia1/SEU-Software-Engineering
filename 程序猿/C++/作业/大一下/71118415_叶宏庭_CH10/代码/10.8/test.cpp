# include <iostream>
# include "IntegerSet.h"

using namespace std;

int main()
{
	int a[5] = { 15,23,45,34,55 };
	int b[5] = { 17,23,43,12,55 };
	IntegerSet set1(a, sizeof(a) / 4);
	IntegerSet set2(b, sizeof(b) / 4);
	cout << "set1:";
	set1.printSet();
	cout << "set2:";
	set2.printSet();
	cout << "set1 is equal to set2 ?  " << set1.isEqualTo(set2);
	cout << "\n\n";
	IntegerSet set3 = set1.unionOfSets(set2);
	IntegerSet set4 = set1.intersectionOfSets(set2);
	cout << "union of set1 and set2:";
	set3.printSet();
	cout << "intersection of set1 and set2:";
	set4.printSet();
	cout << "\n\n";
	set3.insertElement(100);
	cout << "set3 is(insert 100):";
	set3.printSet();
	set4.deleteElement(55);
	cout << "set4 is (delete 55):";
	set4.printSet();
	system("pause");
	return 0;
}
