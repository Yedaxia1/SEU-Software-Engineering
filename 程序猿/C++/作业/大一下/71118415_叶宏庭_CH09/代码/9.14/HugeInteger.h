# include <iostream>

using namespace std;

class HugeInteger {
public:
	HugeInteger(string a = "0");
	void input(string );
	void output();
	HugeInteger add(HugeInteger);
	HugeInteger subtract(HugeInteger);
	bool isEqualTo(HugeInteger);
	bool isNotEqualTo(HugeInteger);
	bool isGreaterThan(HugeInteger);
	bool isLessThan(HugeInteger);
	bool isGreaterThanorEqualThan(HugeInteger);
	bool isLessThanorEqualThan(HugeInteger);
	bool isZero(HugeInteger);
private:
	int digits[40];
	bool t;
};