#include "HugeInt.h"
#include<cctype>
using namespace std;

HugeInt::HugeInt(long value)
{
	for (int i = 0; i < digits; i++)
		integer[i] = 0;
	for (int j = digits - 1; value != 0 && j >= 0; j--)
	{
		integer [j] = value % 10;
		value /= 10;
	}
}
HugeInt::HugeInt(const string &number)
{
	for (int i = 0; i < digits; ++i)
		integer[i] = 0;
	int length = number.size();
	for (int j = digits - length, k = 0; j < digits; ++j, ++k)
		if (isdigit(number[k]))
			integer[j] = number[k] - '0';
}
HugeInt HugeInt::operator+(const HugeInt&op2)const
{
	HugeInt temp;
	int carry = 0;
	for (int i = digits - 1; i >= 0; i--)
	{
		temp.integer[i] = integer[i] + op2.integer[i] + carry;
		if (temp.integer[i] > 9)
		{
			temp.integer[i] %= 10;
			carry = 1;
		}
		else
			carry = 0;
	}
	return temp;
}
HugeInt HugeInt::operator+(int op2)const
{
	return *this + HugeInt(op2);
}
HugeInt HugeInt::operator+(const string&op2)const
{
	return *this + HugeInt(op2);
}
ostream& operator<<(ostream &output, const HugeInt &num)
{
	int i;
	for (i = 0; (num.integer[i] == 0) && (i <= HugeInt::digits); ++i)
		;
	if (i == HugeInt::digits)
		output << 0;
	else
		for (; i < HugeInt::digits; ++i)
			output << num.integer[i];
	return output;
}
HugeInt HugeInt::operator*(const HugeInt& num) const
{
	HugeInt op1;
	HugeInt op2;
	for (; !(op1 == num); op1 = op1 + 1)
	{
		op2 = op2 + *this;
	}
	return op2;
}
HugeInt HugeInt::operator*(int num) const
{
	HugeInt op1(num);
	HugeInt op2 = *this * op1;
	return op2;
}
HugeInt HugeInt::operator*(const string& str1) const
{
	HugeInt op1(str1);
	HugeInt op2 = *this * op1;
	return op2;
}
HugeInt HugeInt::operator/(const HugeInt& num) const
{
	HugeInt op1(0);
	HugeInt op2 = num;
	for (; !(op2 > *this); op1=op1+1)
	{
		op2 = op2 + num;
	}
	return op1;
}
HugeInt HugeInt::operator/(int num) const
{
	HugeInt op1(num);
	HugeInt op2 = *this / op1;
	return op2;
}
HugeInt HugeInt::operator/(const string& str1) const
{
	HugeInt op1(str1);
	HugeInt op2 = *this / op1;
	return op2;
}
bool HugeInt::operator==(const HugeInt& num) const
{
	for (int i = 0; i < digits; i++)
	{
		if (integer[i] == num.integer[i])
			continue;
		else
			return 0;
	}
	return 1;
}
bool HugeInt::operator>(const HugeInt& num) const
{
	if (!(*this == num))
	{
		for (int i = 0; i < digits; i++)
		{
			if (integer[i] > num.integer[i])
				return 1;
			else
			{
				if (integer[i] == num.integer[i])
					continue;
				else
					return 0;
			}
		}
	}
	return 0;
}
bool HugeInt::operator<(const HugeInt& num) const
{
	if (!(*this == num))
	{
		if (*this > num)
			return 0;
		else
			return 1;
	}
	return 0;
}