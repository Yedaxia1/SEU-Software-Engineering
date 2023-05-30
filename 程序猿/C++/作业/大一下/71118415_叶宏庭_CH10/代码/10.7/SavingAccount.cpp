# include <iostream>
# include "SavingAccount.h"
# include <iomanip>

using namespace std;

double SavingAccount::annualInterestRate;

SavingAccount::SavingAccount(double a)
{
	this->savingBalance = a;
}
void SavingAccount::calculateMonthlyInterest()
{
	this->savingBalance += this->savingBalance*annualInterestRate / 12.0;
}
void SavingAccount::modifyInterestRate(double a)
{
	SavingAccount::annualInterestRate = a;
}
void SavingAccount::print()
{
	cout <<fixed<<setprecision(2)<< this->savingBalance << endl;
}
