# include <iostream>
# include <string>
# include <algorithm>
# include "Polynomial.h"
using namespace std;

Polynomial::Polynomial(int a,int size)
{
	Arraysize = size;
	term = new int[Arraysize];
	for (int i = 0; i < Arraysize; i++)
		setTerm(i, 0);
	setTerm(0, a);
}
Polynomial::Polynomial(const string& str1,int size)
{
	Arraysize = size;
	term = new int[Arraysize];
	for (int i = 0; i < Arraysize; i++)
		setTerm(i, 0);
	for (unsigned i=0;i<str1.length();i++)
		setTerm(i, (str1[i] - '0'));
}
Polynomial::Polynomial(const Polynomial& a)
{
	Arraysize = a.Arraysize;
	term = new int[Arraysize];
	for (int i = 0; i < Arraysize; i++)
	{
		setTerm(i, a.term[i]);
	}
}
Polynomial::Polynomial(int *a, int size)
{
	Arraysize = size;
	term = new int[Arraysize];
	for (int i = 0; i < Arraysize; i++)
	{
		setTerm(i, a[i]);
	}
}
void Polynomial::setTerm(int a, int b)
{
	term[a] = b;
}
int Polynomial::getTerm(int a) const
{
	return term[a];
}
const Polynomial& Polynomial::operator=(const Polynomial& a)
{
	if (!(Arraysize == a.Arraysize))
	{
		delete[] term;
		Arraysize = a.Arraysize;
		term = new int[Arraysize];
	}
	for (int i = 0; i < Arraysize; i++)
	{
		term[i] = a.term[i];
	}
	return *this;
}
Polynomial Polynomial::operator+(const Polynomial& a) const 
{
	Polynomial op1(0, max(Arraysize, a.Arraysize));
	for (int i = 0; i < Arraysize; i++)
	{
		op1.setTerm(i, term[i] + a.term[i]);
	}
	return op1;
}
Polynomial Polynomial::operator+=(const Polynomial& a) const
{
	Polynomial op1(0, max(Arraysize, a.Arraysize));
	op1 = *this + a;
	return op1;
}
Polynomial Polynomial::operator-(const Polynomial& a) const
{
	Polynomial op1(0, max(Arraysize, a.Arraysize));
	for (int i = 0; i < Arraysize; i++)
	{
		op1.setTerm(i, term[i] - a.term[i]);
	}
	return op1;
}
Polynomial Polynomial::operator-=(const Polynomial& a) const
{
	Polynomial op1(0, max(Arraysize, a.Arraysize));
	op1 = *this - a;
	return op1;
}
Polynomial Polynomial::operator*(const Polynomial& a) const
{
	Polynomial op1(0, Arraysize+a.Arraysize-1);
	for(int i=0;i<Arraysize;i++)
		for (int j = 0; j < Arraysize; j++)
		{
			op1.term[i + j] += term[i] * a.term[j];
		}
	return op1;
}
Polynomial Polynomial::operator*=(const Polynomial& a) const
{
	Polynomial op1(0, Arraysize + a.Arraysize);
	op1 = *this * a;
	return op1;
}
ostream& operator<<(ostream& output, const Polynomial& a)
{
	for (int i = 0; i < a.Arraysize; i++)
	{
		if(a.getTerm(i))
			output << a.getTerm(i) << "X^" << i;
		if (i == a.Arraysize -1)
			break;
		else
		{
			if (a.term[i + 1] < 0);
			else
				output << "+";
		}
	}
	output << endl;
	return output;
}

