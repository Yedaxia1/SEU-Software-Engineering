# include <iostream>
# include "Rational.h"

using namespace std;

int main()
{
	Rational a(1, 4);
	Rational b(2, 7);
	Rational c = a.add(b);
	Rational d = a.sub(b);
	Rational e = a.mul(b);
	Rational f = a.div(b);
	c.print();
	d.print();
	e.print();
	f.print();
	system("pause");
	return 0;
}
