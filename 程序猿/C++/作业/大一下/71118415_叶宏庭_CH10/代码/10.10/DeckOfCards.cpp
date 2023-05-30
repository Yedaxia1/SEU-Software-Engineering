# include <iostream>
# include "Card.h"
# include "DeckOfCards.h"
# include <ctime>



DeckOfCard::DeckOfCard()
	:currentCard(0)
{
	for(int i=0;i<13;i++)
		for (int j = 0; j < 4; j++)
		{
			Card card(i, j);
			deck.push_back(card);
		}
}
void DeckOfCard::shuffle()
{
	currentCard = 0;
	srand(unsigned (time(0)));
	for (currentCard; currentCard < 52; currentCard++)
	{
		int j = rand() % 52;
		Card card=deck[j];
		deck[j] = deck[currentCard];
		deck[currentCard] = card;
	}
}
Card DeckOfCard::dealCard()
{
	return deck[currentCard +1];
}
bool DeckOfCard::moreCards()
{
	if (currentCard == 52)
		return 0;
	else
		return 1;
}