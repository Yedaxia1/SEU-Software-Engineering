#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Term {
	friend class Polynomial;
private:
	float coef;
	int exp;
};

class Polynomial {
public:
	Polynomial(int a) {
		capacity = a;
		term = 0;
		termArray = new Term[capacity];
	}
	void setTerms(float f, int e)
	{
		termArray[term].coef = f;
		termArray[term++].exp = e;
	}
	float getSumValue(float x)
	{
		float sum = 0;
		for (int i = 0; i < term; i++)
		{
			sum += termArray[i].coef * pow(x, termArray[i].exp);
		}
		return sum;
	}
private:
	Term *termArray;  //array of nonzero terms.
	int capacity;          //size of termArray.
	int term;               // number of nonzero terms.
};

int main()
{
	int num;
	cout << "Enter the number of you polynomial terms."<<endl;
	cin >> num;
	Polynomial poly1(num);
	
	float f;
	int e;
	cout << "Enter your polynomial by coef  and exp.(0 0 to end)."<<endl;
	cin >> f >> e;
	while (f != 0)
	{
		poly1.setTerms(f, e);
		cin >> f >> e;
	}
	
	int sub;
	cout << "Enter the value of X.";
	cin >> sub;

	cout << "The value of the polynomial is " << poly1.getSumValue(sub)<<endl;
	system("pause");
}
