# include <iostream>
# include "Student.h"
# include <fstream>
# include <string>
using namespace std;

void main()
{
	fstream index("output.txt", ios::out);
	int idnum = 1;
	char name1[]="";
	char name2[]="";


	cin >> idnum >> name1 >> name2;

	do
	{
		Student student1(idnum, name1, name2);
		student1.print(index);
		cin >> idnum >> name1 >> name2;
	} while (idnum);
	
	return;
}