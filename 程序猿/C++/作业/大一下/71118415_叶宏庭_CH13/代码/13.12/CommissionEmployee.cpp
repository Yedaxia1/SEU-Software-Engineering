#include<iostream>
#include "CommissionEmployee.h"
using namespace std;

CommissionEmployee::CommissionEmployee(const string& first, const string& last, const string& ssn, Date date, double sales, double rate)
	:Employee(first,last,ssn,date)
{
	setGrossSales(sales);
	setCommissionRate(rate);
}
void CommissionEmployee::setCommissionRate(double rate)
{
	commissionRate = ((rate > 0.0 && rate < 1.0) ? rate : 0.0);
}
double CommissionEmployee::getCommissionRate()const
{
	return commissionRate;
}
void CommissionEmployee::setGrossSales(double sales)
{
	grossSales = ((sales < 0.0) ? 0.0 : sales);
}
double CommissionEmployee::getGrossSlaes()const
{
	return grossSales;
}

double CommissionEmployee::earnings()const
{
	return getCommissionRate()* getGrossSlaes();
}
void CommissionEmployee::print()const
{
	cout << "commission employee: ";
	Employee::print();
	cout << "\ngross sales: " << getGrossSlaes() << "; commission rate: " << getCommissionRate();
}