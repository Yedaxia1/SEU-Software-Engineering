# include <iostream>
# include "Rational.h"

using namespace std;

Rational::Rational(int num, int den)
{
	Num = num;
	Den = den;
	reduce();
}
Rational Rational::add(Rational a)
{
	Rational c;
	c.Num = Num * a.Den + Den * a.Num;
	c.Den = Den * a.Den;
	c.reduce();
	return c;
}
Rational Rational::sub(Rational a)
{
	Rational c;
	c.Num = Num * a.Den - Den * a.Num;
	c.Den = Den * a.Den;
	c.reduce();
	return c;
}
Rational Rational::mul(Rational a)
{
	Rational c;
	c.Num = Num * a.Num;
	c.Den = Den * a.Den;
	c.reduce();
	return c;
}
Rational Rational::div(Rational a)
{
	Rational c;
	c.Num = Num * a.Den;
	c.Den = Den * a.Num;
	c.reduce();
	return c;
}
void Rational::print()
{
	cout << Num << "/" << Den << endl;
	cout << (double)Num / Den << endl;
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
