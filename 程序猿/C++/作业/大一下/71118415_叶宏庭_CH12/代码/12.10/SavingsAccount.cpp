# include <iostream>
# include "SavingsAccount.h"

SavingsAccount::SavingsAccount(double a, double b)
	:Account(a)
{
	interestRate = b;
}
double SavingsAccount::calculateInterest()
{
	double Interest = getbalance()*interestRate;
	credit(Interest);
	return Interest;
}