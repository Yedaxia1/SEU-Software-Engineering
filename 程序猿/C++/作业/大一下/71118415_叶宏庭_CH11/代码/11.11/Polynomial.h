# include <iostream>
# include <string>

# ifndef Polynomial_H
# define Polynomial_H
using namespace std;

class Polynomial {
	friend ostream& operator<<(ostream&, const Polynomial&);
public:
	Polynomial(int = 0,int =0);
	Polynomial(const string& ,int size);
	Polynomial(const Polynomial& );
	Polynomial(int *, int);
	const Polynomial& operator=(const Polynomial&);
	Polynomial operator+(const Polynomial&) const ;
	Polynomial operator-(const Polynomial&) const;
	Polynomial operator*(const Polynomial&) const;
	Polynomial operator+=(const Polynomial&) const;
	Polynomial operator-=(const Polynomial&) const;
	Polynomial operator*=(const Polynomial&) const;
	void setTerm(int, int);
	int getTerm(int ) const;
private:
	int Arraysize;
	int  * term;
};



# endif
