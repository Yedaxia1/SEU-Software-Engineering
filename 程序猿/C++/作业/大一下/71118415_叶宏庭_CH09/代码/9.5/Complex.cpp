# include <iostream>
# include "Complex.h"

using namespace std;

Complex::Complex(double real, double imag)
{
	Real = real;
	Imag = imag;
}
Complex Complex::add(Complex a)
{
	Complex c(Real + a.Real, Imag + a.Imag);
	return c;
}
Complex Complex::sub(Complex a)
{
	Complex c(Real - a.Real, Imag - a.Imag);
	return c;
}
void Complex::print()
{
	cout << "(" << Real << "," << Imag << ")" << endl;
}
