# include <iostream>
# include <string.h>
# include <vector>
# include <ctime>
# include <cstdlib>
# include <iomanip>
# include "Card.h"
# include "DeckOfCards.h"

using namespace std;

int main()
{
	DeckOfCard a;
	a.shuffle();
	cout << fixed << left;
	for (int i = 0; i < 52; i++)
	{
		if (!(i % 2))
		{
			cout << setw(20)<< a.deck[i].toString();
		}
		else
		{
			cout << setw(20)<< a.deck[i].toString();
			cout << endl;
		}
	}
	cout << "\n\n";
	a.shuffle();
	for (int i = 0; i < 52; i++)
	{
		if (!(i % 2))
		{
			cout << setw(20) << a.deck[i].toString();
		}
		else
		{
			cout << setw(20) << a.deck[i].toString();
			cout << endl;
		}
	}
	return 0;
}