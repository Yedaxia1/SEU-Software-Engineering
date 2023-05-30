# include <iostream>
# include <vector>
# ifndef DeckOfCards_h
# define DeckOfCards_h
# include "Card.h"

class DeckOfCard {
public:
	DeckOfCard();
	void shuffle();
	vector <Card> deck;
	Card dealCard();
	bool moreCards();
private:
	int currentCard;
};
# endif
