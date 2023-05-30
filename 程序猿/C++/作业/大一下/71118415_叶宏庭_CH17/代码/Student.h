# ifndef STUDENT_H
# define STUDENT_H

using namespace std;

# include <string>
# include <fstream>

class Student {
public:
	Student(int, char*, char*);
	~Student();
	void set(int, char*, char*);
	void print(fstream &);
private:
	int IDnumber;
	char* FirstName;
	char* LastName;
};


# endif
