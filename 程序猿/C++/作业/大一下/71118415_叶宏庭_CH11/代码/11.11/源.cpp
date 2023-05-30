# include <iostream>
# include "Polynomial.h"

using namespace std;

int main()
{
	int num1[5] = { 1,2,3,4,5 };
	int num2[5] = { 5,4,3,2,1 };
	Polynomial a(num1,5);
	Polynomial b(num2,5);
	cout << "a =" << a;
	cout << "b =" << b;
	Polynomial c = a + b;
	Polynomial d = a - b;
	Polynomial e = a * b;
	cout <<"a + b ="<< c;
	cout <<"a - b =" << d;
	cout << "a * b =" << e;
	system("pause");
	return 0;
}