# include <iostream>

using namespace std;

class Rational {
	int Num, Den;
public:
	Rational(int num = 0, int den = 1);
	Rational add(Rational);
	Rational sub(Rational);
	Rational mul(Rational);
	Rational div(Rational);
	void print();
	void reduce();
	int biggest(int, int);
};

