# include <iostream>
# include "Account.h"
# include "CheckingAccount.h"
# include "SavingsAccount.h"

using namespace std;

int main()
{
	Account num1(2000.0);
	SavingsAccount num2(2000.0, 0.03);
	CheckingAccount num3(2000.0, 10.0);
	cout << "Balance of num1:" << num1.getbalance() << endl;
	cout << "Balance of num2:" << num2.getbalance() << endl;
	cout << "Balance of num3:" << num3.getbalance() << endl;
	cout << "\n";

	num1.credit(1000.0);
	num2.credit(1000.0);
	num3.credit(1000.0);
	cout << "Balance of num1:" << num1.getbalance() << endl;
	cout << "Balance of num2:" << num2.getbalance() << endl;
	cout << "Balance of num3:" << num3.getbalance() << endl;
	cout << "\n";

	num1.debit(1000.0);
	num2.debit(1000.0);
	num3.debit(1000.0);
	cout << "Balance of num1:" << num1.getbalance() << endl;
	cout << "Balance of num2:" << num2.getbalance() << endl;
	cout << "Balance of num3:" << num3.getbalance() << endl;
	cout << "\n";

	cout << "Balance of num2 (before calculateInterest):" << num2.getbalance() << endl;
	num2.calculateInterest();
	cout << "Balance of num2 (after calculateInterest):" << num2.getbalance() << endl;
	cout << "\n";

	system("pause");
	return 0;
}