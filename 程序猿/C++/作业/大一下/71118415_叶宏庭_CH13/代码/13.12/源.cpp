#include<iostream>
#include<iomanip>
#include<vector>
#include"Employee.h"
#include"SalariedEmployee.h"
#include"CommissionEmployee.h"
#include"BasePlusCommissionEmployee.h"
# include "Date.h"
using namespace std;

void virtualViaReference(const Employee&,int);

int main()
{
	cout << fixed << setprecision(2);

	SalariedEmployee salariedEmployee("John", "Smith", "111-11-1111",Date(1,1,1999), 800.0);
	CommissionEmployee commissionEmployee("Sue", "Jones", "333-33-3333", Date(5,20,2000),10000, .06);
	BasePlusCommissionEmployee basePlusCommissionEmployee("Bob", "Lewis", "444-44-4444",Date(7,12,2003),5000, .04, 300);
	
	vector <Employee *> employee(3);

	employee[0] = &salariedEmployee;
	employee[1] = &commissionEmployee;
	employee[2] = &basePlusCommissionEmployee;

	int month = 1;
	for(;month<=12;month++)
		for (size_t i = 0; i < employee.size() ; i++)
			virtualViaReference(*employee[i], month);

}

void virtualViaReference(const Employee& baseClassRef,int month)
{
	baseClassRef.print();
	if(baseClassRef.getBirthMonth()==month)
		cout << "\nearned $" << baseClassRef.earnings()+100.00 <<"    (BirthMonth ! !)"<< "\n\n";
	else
		cout << "\nearned $" << baseClassRef.earnings() << "\n\n";

}