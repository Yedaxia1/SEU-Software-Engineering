# include <iostream>
# include "Account.h"

# ifndef CheckingAccount_h
# define CheckingAccount_h
class CheckingAccount :public Account
{
public:
	CheckingAccount(double a=0, double b=0);
	void credit(double);
	void debit(double);
private:
	double Checkingfee;
};

# endif
