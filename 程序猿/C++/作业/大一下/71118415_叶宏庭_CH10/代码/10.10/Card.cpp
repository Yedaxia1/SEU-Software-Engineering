# include <iostream>
# include <cstdlib>
# include <iomanip>
# include "Card.h"
# include <string>
using namespace std;

string Card::faceName[] = { "One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King" };
string Card::suitName[] = { "Heart","Diamond","Club","Spade" };
Card::Card(int a, int b)
{
	face = a;
	suit = b;
}
Card::Card()
{
	face = 1;
	suit = 1;
}
string Card::toString()
{
	return faceName[face] +" of " + suitName[suit];
}

