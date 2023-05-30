#include <iostream>
using namespace std;

class Polynomial;

class Term {   //Term�����ڴ洢ϵ����ָ��
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
	void setTerms(float f, int e) //������
	{
		if (free == capacity)//��free��capacity����ռ䲻�㣬���¿���˫���ռ�
		{
			capacity *= 2;
			Term *newArray = new Term[capacity];
			for (int i = 0; i < free; i++)      //����ԭ������
				newArray[i] = termArray[i];
			termArray = newArray;
			delete newArray;
		}
		if (start == -1)//�жϵ�ǰ�������Ƿ�Ϊ��һ�μ�����
			start = free;
		finish = free;   //����������free��λ�ã�����finish��free
		termArray[free].coef = f;
		termArray[free].exp = e;
		free++;    //free����һλ
	}
	void setTerms(Term a)
	{
		setTerms(a.coef, a.exp);
	}
	void insertTerms(float f, int e)//Ϊ����ʽ������
	{
		if (e < termArray[finish].exp)//���������ָ��С�����һ���ָ������ֱ���ں����
		{
			setTerms(f, e);
		}
		else
			for (int i = start; i <= finish; i++)//�������飬�ҵ�Ӧ�ò����λ��
			{
				if (e == termArray[i].exp)//��ָ������ĳһ��ָ������ϵ����һ�𼴿�
				{
					termArray[i].coef += f;
					break;
				}
				else if (e > termArray[i].exp)//��ָ�����ִ���ĳһ���ָ����������ڸ����λ��
				{
					Term temp1 = termArray[i];//���ں���ԭ�е�ÿһ��
					Term temp2;   //���ں���ԭ�е�ÿһ��
					termArray[i].coef = f;
					termArray[i].exp = e;
					for (int j = i + 1; j <= finish; j++)
					{
						temp2 = temp1;//��ǰһ��ŵ�temp2��
						temp1 = termArray[j];//����ǰ�����temp1��
						termArray[j] = temp2;//����ǰ���Ϊǰһ�temp2��
					}
					setTerms(temp1);//��������ԭ�������һ��
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
		for (int i = start, j = a.start; i <= finish && j <= a.finish;)//��������ͬʱ�����㷨������ע����O����ԭ����ʽ��a������Ҫ���ϵĶ���ʽ�����ӷ�ΪO+a��
		{
			if (termArray[i].exp > a.termArray[j].exp)//��O��ָ������a��ָ����������ΪO�ĸ���
			{
				c.setTerms(termArray[i].coef, termArray[i].exp);
				i++; //O��Ҫ����һ��
			}
			else if (termArray[i].exp == a.termArray[j].exp)//��O��ָ������a��ָ��������ΪO��a��ϵ����ӣ�ָ������
			{
				c.setTerms(termArray[i].coef + a.termArray[j].coef, termArray[i].exp);
				i++;//O��Ҫ����һ��
				j++;//a��Ҫ����һ��
			}
			else if (termArray[i].exp < a.termArray[j].exp)//��O��ָ��С��a��ָ��������Ϊa�ĸ���
			{
				c.setTerms(a.termArray[j].coef, a.termArray[j].exp);
				j++;//a��Ҫ����һ��
			}
			if (i == finish + 1 && j <= a.finish)//��O�������ˣ���a��ʣ������뵽������
				for (int m = j; m <= a.finish; m++)
					c.setTerms(a.termArray[m].coef, a.termArray[m].exp);
			else if (j == a.finish + 1 && i <= finish)//��a�������ˣ���O��ʣ������뵽������
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
		for (int i = start; i <= finish; i++)//����O��ÿһ�����a�ĵ�һ��洢������ע����O����ԭ����ʽ��a������Ҫ���ϵĶ���ʽ�����˷�ΪO*a��
		{
			c.setTerms(termArray[i].coef*a.termArray[a.start].coef, termArray[i].exp + a.termArray[a.start].exp);
		}
		for (int i = a.start + 1; i <= a.finish; i++)//��������O��ÿһ�����a��ÿһ������뵽��һ���Ľ����
			for (int j = start; j <= finish; j++)
				c.insertTerms(termArray[j].coef*a.termArray[i].coef, termArray[j].exp + a.termArray[i].exp);//������
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
