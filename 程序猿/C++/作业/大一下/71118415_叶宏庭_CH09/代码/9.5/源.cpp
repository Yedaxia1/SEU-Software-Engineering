# include <iostream>
# include "Complex.h"

using namespace std;

int main()
{
	Complex a(1, 2);
	Complex b(2, 5);
	Complex c = a.add(b);
	Complex d = a.sub(b);
	c.print();
	d.print();
	system("pause");
	return 0;
}
