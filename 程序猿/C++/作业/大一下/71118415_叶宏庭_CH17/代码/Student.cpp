# include <iostream>
# include "Student.h"
# include <string>
# include <iomanip>
# include <fstream>

Student::Student(int a, char* b, char* c)
{
	set(a, b, c);
}

Student::~Student()
{
	delete[]FirstName;
	delete[]LastName;
}
void Student::set(int a, char* b, char* c)
{
	IDnumber = a;
	FirstName = new char[strlen(b) + 1];
	for (int i = 0; i <= strlen(b); i++)
		FirstName[i] = b[i];
	LastName = new char[strlen(c) + 1];
	for (int i = 0; i <= strlen(c); i++)
		LastName[i] = c[i];
}

void Student::print(fstream &index)
{
	index << setw(10) << IDnumber << setw(10) << FirstName << setw(15) << LastName << endl;
}