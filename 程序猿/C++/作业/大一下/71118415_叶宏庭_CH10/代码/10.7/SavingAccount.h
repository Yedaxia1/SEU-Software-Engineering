# include <iostream>
# ifndef SavingAccount_h
# define SavingAccount_h

class SavingAccount {
private:
	static double annualInterestRate;
	double savingBalance;
public:
	SavingAccount(double a = 0);
	void calculateMonthlyInterest();
	void print();
	static void modifyInterestRate(double);
};
# endif
