# include "HugeInteger.h"

using namespace std;

HugeInteger::HugeInteger(string a)
{
	int Long = a.length();
	int left = 39;
	for (int i = Long-1; i >=0; i--,left--)
	{
		digits[left] = (int)a[i] - 48;
	}
	for (int i = left; i >= 0; i--)
		digits[i] = 0;
}
void HugeInteger::input(string a)
{
	int Long = a.length();
	int left = 39;
	for (int i = Long - 1; i >= 0; i--, left--)
	{
		digits[left] = (int)a[i] - 48;
	}
	for (int i = left; i >= 0; i--)
		digits[i] = 0;
}
void HugeInteger::output()
{
	bool k = 0;
	if (digits[0] != 0)
		k = 1;
	if (!t)
		cout << "-";
	for (int i = 0; i < 40 ; i++)
	{
		if (digits[i] != 0)
			k = 1;
		if(k)
			cout << digits[i];
	}
	cout << endl;
}
HugeInteger HugeInteger::add(HugeInteger a)
{
	HugeInteger c;
	for (int i = 39; i > 0; i--)
	{
		c.digits[i] = digits[i] + a.digits[i];
		if (c.digits[i] > 9)
		{
			c.digits[i] = c.digits[i] % 10;
			c.digits[i - 1]++;
		}
	}
	c.digits[0] += digits[0] + a.digits[0];
	if (c.digits[0] >= 10)
	{
		cout << "Error adding !!  Too big result !!!" << endl;
		return c;
	}
	return c;
}
HugeInteger HugeInteger::subtract(HugeInteger a)
{
	HugeInteger c;
	for (int i = 39; i >= 0; i--)
		c.digits[i] = digits[i] - a.digits[i];
	if (isLessThan(a))
	{
		for (int i = 0; i < 40; i++)
			c.digits[i] = -c.digits[i];
		for (int i = 39; i > 0; i--)
		{
			if (c.digits[i] < 0)
			{
				c.digits[i] += 10;
				c.digits[i - 1]--;
			}
		}
		c.t = 0;
	}
	else
	{
		for (int i = 39; i > 0; i--)
		{
			if (c.digits[i] < 0)
			{
				c.digits[i] += 10;
				c.digits[i - 1]--;
			}
		}
	}
	return c;
}
bool HugeInteger::isEqualTo(HugeInteger a)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (digits[i] != a.digits[i])
		{
			k = 0;
			break;
		}
	}
	return k;
}
bool HugeInteger::isNotEqualTo(HugeInteger a)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (digits[i] != a.digits[i])
		{
			k = 0;
			break;
		}
	}
	return !k;
}
bool HugeInteger::isGreaterThan(HugeInteger a)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (digits[i] < a.digits[i])
		{
			k = 0;
			break;
		}
		else
			if (digits[i] > a.digits[i])
				break;
		if (i == 39 && (digits[i] == a.digits[i]))
			k = 0;
	}
	return k;
}
bool HugeInteger::isLessThan(HugeInteger a)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (digits[i] < a.digits[i])
		{
			k = 0;
			break;
		}
		else
			if (digits[i] > a.digits[i])
				break;
		if (i == 39 && (digits[i] == a.digits[i]))
			k = 1;
	}
	return !k;
}
bool HugeInteger::isGreaterThanorEqualThan(HugeInteger a)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (digits[i] < a.digits[i])
		{
			k = 0;
			break;
		}
		else
			if (digits[i] > a.digits[i])
				break;
	}
	return k;
}
bool HugeInteger::isLessThanorEqualThan(HugeInteger a)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (digits[i] < a.digits[i])
		{
			k = 0;
			break;
		}
		else
			if (digits[i] > a.digits[i])
				break;
	}
	return !k;
}
bool HugeInteger::isZero(HugeInteger)
{
	bool k = 1;
	for (int i = 0; i < 40; i++)
	{
		if (!digits[i])
		{
			k = 0;
			break;
		}
	}
	return k;
}