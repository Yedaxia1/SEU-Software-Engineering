# include <iostream>
# include "SavingAccount.h"

using namespace std;

int main()
{
	SavingAccount save1(2000.00);
	SavingAccount save2(3000.00);
	SavingAccount::modifyInterestRate(0.03);
	save1.calculateMonthlyInterest();
	save2.calculateMonthlyInterest();
	cout << "annualInterestRate:" << 0.03 << endl;
	cout << "save1:";
	save1.print();
	cout << "save2:";
	save2.print();
	cout << "\n\n";
	SavingAccount::modifyInterestRate(0.04);
	save1.calculateMonthlyInterest();
	save2.calculateMonthlyInterest();
	cout << "annualInterestRate:" << 0.04 << endl;
	cout << "save1:";
	save1.print();
	cout << "save2:";
	save2.print();
	system("pause");
	return 0;
}
