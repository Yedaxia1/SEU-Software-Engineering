#include <iostream>
using namespace std;

class Polynomial;

class Term {   //Term类用于存储系数与指数
	friend class Polynomial;
private:
	float coef;
	int exp;
};

class Polynomial {
public:
	Polynomial()
	{
		start = -1;
		finish = -1;
	}
	void setStart(int a)
	{
		start = a;
	}
	void setFinish(int a)
	{
		finish = a;
	}
	void setTerms(float f, int e) //加入项
	{
		if (free == capacity)//若free＝capacity，则空间不足，重新开创双倍空间
		{
			capacity *= 2;
			Term *newArray = new Term[capacity];
			for (int i = 0; i < free; i++)      //拷贝原有数据
				newArray[i] = termArray[i];
			termArray = newArray;
			delete newArray;
		}
		if (start == -1)//判断当前加入项是否为第一次加入项
			start = free;
		finish = free;   //加入的项放在free的位置，所以finish＝free
		termArray[free].coef = f;
		termArray[free].exp = e;
		free++;    //free后移一位
	}
	void setTerms(Term a)
	{
		setTerms(a.coef, a.exp);
	}
	void insertTerms(float f, int e)//为多项式插入项
	{
		if (e < termArray[finish].exp)//若插入的项指数小于最后一项的指数，则直接在后面加
		{
			setTerms(f, e);
		}
		else
			for (int i = start; i <= finish; i++)//遍历数组，找到应该插入的位置
			{
				if (e == termArray[i].exp)//若指数等于某一项指数，则将系数加一起即可
				{
					termArray[i].coef += f;
					break;
				}
				else if (e > termArray[i].exp)//若指数出现大于某一项的指数，则插入在该项的位置
				{
					Term temp1 = termArray[i];//用于后移原有的每一项
					Term temp2;   //用于后移原有的每一项
					termArray[i].coef = f;
					termArray[i].exp = e;
					for (int j = i + 1; j <= finish; j++)
					{
						temp2 = temp1;//将前一项放到temp2中
						temp1 = termArray[j];//将当前项放入temp1中
						termArray[j] = temp2;//将当前项改为前一项（temp2）
					}
					setTerms(temp1);//在最后加上原本的最后一项
				}
			}
	}
	void getTerms()
	{
		for (int i = start; i <= finish; i++)
		{
			if (i == finish)
			{
				if (termArray[finish].exp == 0)
					cout << termArray[finish].coef << endl;
				else
				{
					if (termArray[finish].coef == 1)
						cout << "X^" << termArray[finish].exp << endl;
					else
						cout << termArray[finish].coef << "X^" << termArray[finish].exp << endl;
				}
			}
			else
			{
				if (termArray[i].coef == 1)
					cout << "X^" << termArray[i].exp << "+";
				else
					cout << termArray[i].coef << "X^" << termArray[i].exp << "+";
			}
		}
	}
	Polynomial operator+(Polynomial a)
	{
		return addPolynomial(a);
	}
	Polynomial addPolynomial(Polynomial a)
	{
		Polynomial c;
		for (int i = start, j = a.start; i <= finish && j <= a.finish;)//两个数组同时后移算法（后面注释以O代表原多项式，a代表需要加上的多项式，即加法为O+a）
		{
			if (termArray[i].exp > a.termArray[j].exp)//若O的指数大于a的指数，则结果的为O的该项
			{
				c.setTerms(termArray[i].coef, termArray[i].exp);
				i++; //O需要后移一项
			}
			else if (termArray[i].exp == a.termArray[j].exp)//若O的指数等于a的指数，则结果为O，a的系数相加，指数不变
			{
				c.setTerms(termArray[i].coef + a.termArray[j].coef, termArray[i].exp);
				i++;//O需要后移一项
				j++;//a需要后移一项
			}
			else if (termArray[i].exp < a.termArray[j].exp)//若O的指数小于a的指数，则结果为a的该项
			{
				c.setTerms(a.termArray[j].coef, a.termArray[j].exp);
				j++;//a需要后移一项
			}
			if (i == finish + 1 && j <= a.finish)//若O遍历完了，则将a的剩余项加入到结果最后
				for (int m = j; m <= a.finish; m++)
					c.setTerms(a.termArray[m].coef, a.termArray[m].exp);
			else if (j == a.finish + 1 && i <= finish)//若a遍历完了，则将O的剩余项加入到结果最后
				for (int m = i; i <= finish; m++)
					c.setTerms(termArray[m].coef, termArray[m].exp);
		}
		return c;
	}
	Polynomial operator*(Polynomial a)
	{
		return multiplyPolynomial(a);
	}
	Polynomial multiplyPolynomial(Polynomial a)
	{
		Polynomial c;
		for (int i = start; i <= finish; i++)//先用O的每一项乘以a的第一项并存储（后面注释以O代表原多项式，a代表需要乘上的多项式，即乘法为O*a）
		{
			c.setTerms(termArray[i].coef*a.termArray[a.start].coef, termArray[i].exp + a.termArray[a.start].exp);
		}
		for (int i = a.start + 1; i <= a.finish; i++)//接下来用O的每一项乘以a的每一项，并插入到上一步的结果中
			for (int j = start; j <= finish; j++)
				c.insertTerms(termArray[j].coef*a.termArray[i].coef, termArray[j].exp + a.termArray[i].exp);//插入项
		return c;
	}
private:
	static Term *termArray;  //array of nonzero terms.
	static int capacity;          //size of termArray.
	static int free;               // number of nonzero terms.
	int start, finish;
};

int Polynomial::capacity = 100;
Term *Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

int main()
{
	Polynomial a;
	cout << "Enter your a polynomial." << endl;
	float coef;
	int exp;
	cin >> coef >> exp;
	while (coef != 0)
	{
		a.setTerms(coef, exp);
		cin >> coef >> exp;
	}
	cout << "a=";
	a.getTerms();
	Polynomial b;
	cout << "Enter your b polynomial." << endl;
	cin >> coef >> exp;
	while (coef != 0)
	{
		b.setTerms(coef, exp);
		cin >> coef >> exp;
	}
	cout << "b=";
	b.getTerms();
	Polynomial c = a + b;
	cout << "a+b=";
	c.getTerms();
	Polynomial d = a * b;
	cout << "a*b=";
	d.getTerms();
	system("pause");
}
