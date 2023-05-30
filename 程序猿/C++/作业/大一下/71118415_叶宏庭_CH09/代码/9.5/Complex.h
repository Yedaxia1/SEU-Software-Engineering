# include <iostream>
#ifndef Complex_h
#define Complex_h

using namespace std;

class Complex {
	double Real, Imag;
public:
	Complex(double real = 0, double imag = 0);
	Complex add(Complex);
	Complex sub(Complex);
	void print();
};

#endif

