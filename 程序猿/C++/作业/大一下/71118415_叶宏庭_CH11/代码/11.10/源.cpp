# include <iostream>
# include <string>
# include "Rational.h"

using namespace std;

int main()
{
	Rational a(1, 4);
	Rational b(2, 7);
	cout << "a + b =" << a + b ;
	cout << "a - b =" << a - b ;
	cout << "a * b ="<<a * b;
	cout << "a / b =" << a / b;
	cout << "a * 5 =" << a * 5;
	system("pause");
	return 0;
}
