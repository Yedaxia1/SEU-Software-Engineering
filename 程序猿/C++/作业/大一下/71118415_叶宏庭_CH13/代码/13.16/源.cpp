# include <iostream>
# include <typeinfo>
# include <vector>
# include <iomanip>
# include "Account.h"
# include "SavingsAccount.h"
# include "CheckingAccount.h"

using namespace std;

int main()
{
	cout << fixed << setprecision(2);
	SavingsAccount num0(2000.0, 0.05);
	SavingsAccount num2(3000.0, 0.05);	
	CheckingAccount num1(2000.0, 10.0);
	CheckingAccount num3(3000.0, 10.0);
	vector <Account*> account(4);
	account[0] = &num0;
	account[1] = &num1;
	account[2] = &num2;
	account[3] = &num3;
	for (size_t i = 0; i < account.size(); ++i)
	{
		cout << "Balance of num" << i << ": ";
		account[i]->print();
	}
	cout << "\n\n";
	cout << "credit 1000.00 to each account:" << endl;
	for (size_t i = 0; i < account.size(); ++i)
	{
		account[i]->credit(1000.0);
		SavingsAccount *temp = dynamic_cast<SavingsAccount*>(account[i]);
		if (temp!=0)
		{
			temp->calculateInterest();
		}
		cout << "Balance of num" << i << ": ";
		account[i]->print();
	}
	system("pause");
	return 0;
}