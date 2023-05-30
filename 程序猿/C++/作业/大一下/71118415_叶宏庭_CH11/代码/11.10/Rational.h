#ifndef Rational_h
#define Rational_h
# include <iostream>
# include <string>

using namespace std;

class Rational {
	friend 	ostream& operator<<(ostream &, const Rational&);
	int Num, Den;
public:
	Rational(int num = 0, int den = 1);
	Rational operator+(const Rational& ) const;
	Rational operator+(int) const;
	Rational operator+(const string&) const;
	Rational operator-(const Rational&) const;
	Rational operator-(int) const;
	Rational operator-(const string&) const;
	Rational operator*(const Rational&) const;
	Rational operator*(int) const;
	Rational operator*(const string&) const;
	Rational operator/(const Rational&) const;
	Rational operator/(int) const;
	Rational operator/(const string&) const;
	bool operator==(const Rational&) const;
	bool operator!=(const Rational&) const;
	bool operator>(const Rational&) const;
	bool operator<(const Rational&) const;
	void reduce();
	int StringToInt(const string&) const;
	int biggest(int, int);
};

#endif

