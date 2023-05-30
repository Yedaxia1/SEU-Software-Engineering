# include <iostream>
# include "HugeInteger.h"

using namespace std;

int main()
{
	HugeInteger hugeinteger1("100000000000000000000");
	HugeInteger hugeinteger2("200000000000000000000000000");
	HugeInteger hugeinteger3 = hugeinteger1.add(hugeinteger2);
	HugeInteger hugeinteger4 = hugeinteger1.subtract(hugeinteger2);
	hugeinteger3.output();
	hugeinteger4.output();
	return 0;
}