# include <iostream>
# include "Account.h"

# ifndef SavingsAccount_h
# define SavingsAccount_h
class SavingsAccount : public Account
{
public:
	SavingsAccount(double = 0, double = 0);
	double calculateInterest();
private:
	double interestRate;
};

# endif
