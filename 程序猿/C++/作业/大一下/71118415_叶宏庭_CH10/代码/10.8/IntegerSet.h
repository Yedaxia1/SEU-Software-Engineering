# include <iostream>
# include <vector>
# ifndef IntegerSet_h
# define IntegerSet_h

using namespace std;

class IntegerSet {
private:
	const static int size = 101;
	vector<bool> set;
public:
	IntegerSet();
	IntegerSet(int *a, int l);
	IntegerSet unionOfSets(IntegerSet a);
	IntegerSet intersectionOfSets(IntegerSet a);
	void insertElement(int k);
	void deleteElement(int k);
	void printSet();
	bool isEqualTo(IntegerSet a);
};
# endif
