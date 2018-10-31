struct card
{       char num;
        char suit;
};
typedef struct card card;

void printDeck(int deckSize,card deck[deckSize])
{
	int i;
	for(i=0;i<deckSize;i++)
	{
		if(deck[i].num == '0')
			printf("%s of %c\n","10",deck[i].suit);
		else
			printf("%2c of %c\n",deck[i].num,deck[i].suit);
	}
	return;
}

void shuffleDeck(int deckSize,card deck[deckSize])
{
	int i;
	char tn,ts;
	srand(time(NULL));
	for(i=0;i<deckSize;i++)
	{//itterate over the whole deck
		//randomly choose a card to switch
		int choice = (rand()%deckSize);//Current card with
		tn = deck[i].num;
		ts = deck[i].suit;
		deck[i].num = deck[choice].num;
		deck[i].suit = deck[choice].suit;
		deck[choice].num = tn;
		deck[choice].suit = ts;
	}
}

void makeDeck(card deck[52])
{
	int s,n,cardnum=0;
	char suits[4] = {'S','C','D','H'};
	char vals[13] = {'A','2','3','4','5','6','7','8','9','0','J','Q','K'};//10 is 0
	for(s = 0;s < 4;s++)
	{
		for(n = 0; n < 13;n++)
		{
			deck[cardnum].suit = suits[s];
			deck[cardnum].num = vals[n];//10s will be 0
			cardnum++;
		}
	}
	return;
}
