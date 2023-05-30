# include <iostream>
# include <string>
# include "Rational.h"

using namespace std;

Rational::Rational(int num, int den)
{
	if (den == 0)
	{
		den = 1;
		cout << "Change denominator from 0 to 1;";
	}
	if (den < 0)
	{
		den = -den;
		num = -num;
	}
	Num = num;
	Den = den;
	reduce();
}
Rational Rational::operator+(const Rational& a) const
{
	Rational c;
	c.Num = Num * a.Den + Den * a.Num;
	c.Den = Den * a.Den;
	c.reduce();
	return c;
}
Rational Rational::operator+(int a) const
{
	Rational op1(a, 1);
	Rational c = *this + op1;
	return c;
}
Rational Rational::operator+(const string& str1) const
{
	int a = StringToInt(str1);
	Rational c = *this + a;
	return c;
}
Rational Rational::operator-(const Rational& a) const
{
	Rational c;
	c.Num = Num * a.Den - Den * a.Num;
	c.Den = Den * a.Den;
	c.reduce();
	return c;
}
Rational Rational::operator-(int a) const
{
	Rational op1(a, 1);
	Rational c = *this - op1;
	return c;
}
Rational Rational::operator-(const string& str1) const
{
	int a = StringToInt(str1);
	Rational c = *this - a;
	return c;
}
Rational Rational::operator*(const Rational& a) const
{
	Rational c;
	c.Num = Num * a.Num;
	c.Den = Den * a.Den;
	c.reduce();
	return c;
}
Rational Rational::operator*(int a) const
{
	Rational op1(a, 1);
	Rational c = *this *op1;
	return c;
}
Rational Rational::operator*(const string& str1) const
{
	int a = StringToInt(str1);
	Rational c = *this + a;
	return c;
}
Rational Rational::operator/(const Rational& a) const
{
	Rational c;
	c.Num = Num * a.Den;
	c.Den = Den * a.Num;
	c.reduce();
	return c;
}
Rational Rational::operator/(int a) const
{
	Rational op1(a, 1);
	Rational c = *this + op1;
	return c;
}
Rational Rational::operator/(const string& str1) const
{
	int a = StringToInt(str1);
	Rational c = *this + a;
	return c;
}
bool Rational::operator==(const Rational& a) const
{
	if (Num == a.Num&&Den == a.Den)
		return 1;
	return 0;
}
bool Rational::operator!=(const Rational& a) const
{
	if (*this == a)
		return 0;
	return 1;
}
bool Rational::operator>(const Rational& a) const
{
	if (!(*this == a))
	{
		if (Num*a.Den > Den*a.Num)
			return 1;
		else
			return 0;
	}
	return 0;
}
bool Rational::operator<(const Rational& a) const
{
	if (*this > a)
		return 0;
	return 1;
}
ostream& operator<<(ostream & output, const Rational& a)
{
	output << a.Num << "/" << a.Den << endl;
	return output;
}
int Rational::biggest(int a, int b)
{
	a = abs(a); b = abs(b);
	if (a < b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	if (b == 0)
		return a;
	else
		return biggest(b, a%b);
}
void Rational::reduce()
{
	int gcd = biggest(Num, Den);
	Num = Num / gcd;
	Den = Den / gcd;
}
int Rational::StringToInt(const string& str1) const
{
	int size = str1.length();
	int a = 0;
	for (int i = 0; i < size; i++)
	{
		a = a * 10 + (str1[i] - '0');
	}
	return a;
}
