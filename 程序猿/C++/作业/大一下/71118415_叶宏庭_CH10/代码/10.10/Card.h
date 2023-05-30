# include <iostream>
# include <string>
# ifndef Card_h
# define Card_h
using namespace std;

class Card{
private:
	int face;
	int suit;
public:
	Card(int, int);
	Card();
	static const int totalFaces = 13;
	static const int totalSuits = 4;
	static string faceName[totalFaces];
	static string suitName[totalSuits];
	string toString();
};
# endif
