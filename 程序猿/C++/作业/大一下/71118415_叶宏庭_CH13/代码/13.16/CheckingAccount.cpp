# include <iostream>
# include "CheckingAccount.h"
using namespace std;

CheckingAccount::CheckingAccount(double a, double b)
	:Account(a)
{
	Checkingfee = b;
}
void CheckingAccount::credit(double a)
{
	Account::credit(a - Checkingfee);
}
bool CheckingAccount::debit(double a)
{
	if (Account::debit(a))
	{
		Account::debit(Checkingfee);
		return true;
	}
	else
	{
		cout << "Error ! (Balance is not enough)";
		return false;
	}
}