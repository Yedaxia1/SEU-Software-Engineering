# include <iostream>

# ifndef Account_h
# define Account_h
using namespace std;

class Account {
public:
	Account(double a = 0)
	{
		if (a >= 0)
			balance = a;
		else
		{
			balance = 0;
			cout << "Error input !";
		}
	}
	virtual void credit(double a) { balance += a; };
	virtual bool debit(double a)
	{
		if (balance >= a)
		{
			balance -= a;
			return true;
		}
		else
		{
			cout << "Debit amount exceeded account balance.";
			return false;
		}
	}
	double getbalance() { return balance; };
	void print() { cout << getbalance() << endl; };
private:
	double balance;
};
#endif

