#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
/*Black Jack By Christopher Loutsch

HOW TO USE
-this game follows most casino rules-
1.The goal is to get as close to 21 as you can or at least higher than the dealer.
2.Hitting means that you are going to take another card
3.Staying means that you are staying with your score and it is now the dealers turn
4.The dealer must hit until they are at 17 or higher
5.Scoring is as follows
	Player scores higher than dealer: 50 points
	Dealer bust: 100 points
	Player scores lower than dealer: 25 points
	Push (Player ties Dealer): No Points
6.There is no betting in this version because I don't want Cody to become addicted to gambling and/or lose all of his $$

REQUREMENTS MET FOR CLASS
1.Strings
2.Structures
3.Linked Lists
4.Stack
5.Custom Header File
6.Pass By Reference

1.I use strings in my deck.h header file when creating the deck.
  The strings hold all of the possible chars for the deck including the number values
  and the suits.
2.I use two different structures. The first structure is used when I am making my deck
  in the deck.h file. It holds the requirements for a 'card' structure. The second struct
  that I use is my hand struct, which is a part of my linked lists.
3.I use linked lists for my player hand and dealer hand.
4.My linked lists are stacks. The hands can be added to with my push function
  and things can be removed with my pop function. The hands are of course last in last out.
5.I use a custom header file for my functions to create a deck. Te file is called deck.h.
6.Pass by reference is used when I mutate my score variable and access it when printing my header
  you can see the score change every time you choose to play again. This is done with a pointer to the score var.
  normal player win += 50 points, dealer bust += 100 points, player loss -= 25 points
*/

struct hand
{//This will store a players card when they draw it from the deck
	char num;
	char suit;
	struct hand *next;
};
typedef struct hand hand;

int getHandVal(hand* head);
int resetAces(hand* head);
hand* push(hand* head,int deckSize,card deck[deckSize],int pos);
hand* pop(hand* node);
void dealerTurn(int handValue,hand* dhhead,int deckSize,card deck[deckSize],int pos,int *sc);
void printHand(hand* head);
void printHeader();

int main()
{
	int score = 0;
	char playAgain = 'y';
	while(playAgain == 'y'||playAgain == 'Y')
	{
		int *sc = &score;
		hand* head=NULL;//pointer to players hand linked list
		hand* dhhead = NULL;//pointer to dealers hand linked list
		int choice = 1;
		int pos = 0;//allows the user to walk through the deck, which is stored in an array
		card deck[52];
		makeDeck(deck);
		shuffleDeck(52,deck);
		printHeader(sc);//Prints the blackjack header
		dhhead = push(dhhead,52,deck,pos);//dealer take first card
		pos++;
		//run a turn
		while(choice != 2)
		{
			int handValue=0,choice=0;
			head = push(head,52,deck,pos);
			pos++;
			handValue = getHandVal(head);
			if(handValue > 21)//Check if there are aces and change them to 1 if you went over 21
				handValue = resetAces(head);
			printHand(head);
			if(handValue>21)
			{
				printf("%d! Oh no! You busted!\n",handValue);
				printf("Dealer Wins!\n");
				*sc -= 25;
				choice = 2;
				break;
			}else if(handValue==21)
			{
				printf("A perfect 21! BLACKJACK\n");
				dealerTurn(handValue,dhhead,52,deck,pos,sc);
				choice = 2;
				break;
			}else
			{
				printf("You are at %d Try to get to 21 or beat the dealer!\n",handValue);
				printf("Dealers visibe card puts him at %d, What would you like to do?\n",getHandVal(dhhead));
				printf("1. Hit Me Dealer!\n");
				printf("2. I'd like to stay\n");
				printf(":");
				scanf(" %d",&choice);
				while(choice<1||choice>2)
				{
					printf("Woah! Just give me a 1 or 2 cowboy: ");
					scanf(" %d",&choice);
				}
				if(choice==2)
				{
					dealerTurn(handValue,dhhead,52,deck,pos,sc);
					break;
				}
			}
		}
		while(head != NULL)
			head = pop(head);
		printf("Would you like to play again (y/n)? ");
		scanf(" %c",&playAgain);//left a space to handle \n
	}
	return 0;
}

int getHandVal(hand* node)
{//Decides how many points your hand is at, this function pretends aces are worth 11
	int handValue = 0;
	hand* tmp;
	tmp = node;
	while(tmp != NULL)
	{
		switch(tmp->num)
		{
			case 'A':handValue+=11;break;
			case '2':handValue+=2;break;
			case '3':handValue+=3;break;
			case '4':handValue+=4;break;
			case '5':handValue+=5;break;
			case '6':handValue+=6;break;
			case '7':handValue+=7;break;
			case '8':handValue+=8;break;
			case '9':handValue+=9;break;
			case '0':handValue+=10;break;
			case 'J':handValue+=10;break;
			case 'Q':handValue+=10;break;
			case 'K':handValue+=10;break;
			default:printf("UNDEFINED VALUE FOUND (%c,%c)\n",tmp->num,tmp->suit);exit(1);
		}
		tmp=tmp->next;
	}
	return handValue;
}

int resetAces(hand* head)
{//if the user goes over, then this function checks to aces to reset their value to 1
	int handValue = 0;
	hand* tmp;
	tmp = head;
	while(tmp != NULL)
	{
		switch(tmp->num)
		{
			case 'A':handValue+=1;break;
			case '2':handValue+=2;break;
			case '3':handValue+=3;break;
			case '4':handValue+=4;break;
			case '5':handValue+=5;break;
			case '6':handValue+=6;break;
			case '7':handValue+=7;break;
			case '8':handValue+=8;break;
			case '9':handValue+=9;break;
	 		case '0':handValue+=10;break;
			case 'J':handValue+=10;break;
			case 'Q':handValue+=10;break;
			case 'K':handValue+=10;break;
			default:printf("UNDEFINED VALUE FOUND (%c,%c)\n",tmp->num,tmp->suit);exit(1);
		}
		tmp=tmp->next;
	}
	return handValue;
}

hand* push(hand* node,int deckSize,card deck[deckSize],int pos)
{//Adds a card to the front of a linked list
	//pos is the place in the deck to take a card from
	hand* tmp;
	tmp = malloc(sizeof(hand));
	if(node == NULL)
	{
		node = tmp;
		tmp->next=NULL;
	}else
	{
		tmp->next=node;
		node = tmp;
	}
	tmp->num=deck[pos].num;
	tmp->suit=deck[pos].suit;
	return node;
}

hand* pop(hand* node)
{//removes the most recently added item from the stack (hand linked list)
	hand* tmp;
	tmp = node;
	if(tmp != NULL)
	{
		tmp = tmp->next;
		free(node);
		node = tmp;
	}

	return node;
}

void dealerTurn(int phv,hand* dhhead,int deckSize,card deck[deckSize],int pos,int *sc)
{//This is the dealer AI, it simply plays by the casino dealer rules
	int dhv = getHandVal(dhhead);//Dealer hand value
	while(dhv<17)
	{
		dhhead = push(dhhead,52,deck,pos);
		pos++;
		dhv = getHandVal(dhhead);
		if(dhv>21)
			dhv = resetAces(dhhead);
	}
	printf("Dealer's hand\n");
	printHand(dhhead);
	printf("Dealer's final score is %d \n",dhv);

	if(phv==dhv)//Test score against player hand value
		printf("PUSH! You tied the dealer!\n");
	else if(dhv>21)
		{printf("Dealer bust! You win!\n");*sc += 100;}
	else if(dhv>phv)
		{printf("Dealer wins! Better luck next time!\n");*sc -= 25;}
	else
		{printf("Congrats! you beat the dealer!\n");*sc += 50;}

	while(dhhead != NULL)//free stack from memory
		dhhead = pop(dhhead);
	return;
}

void printHand(hand* head)
{//prints the cards in a players hand (stack)
//The chars printed for the borders are unreadable by nano
//They will appear as random ^^ but make the borders of the cards
	int count=0;
	hand* tmp;
	tmp = head;

	while(tmp != NULL)
        {//determines how many cards in the hand and prints the tops of the cards
                printf("╔═════╗ ");//prints the tops of the cards
                count++;//Determine how many are in the hand
                tmp=tmp->next;
        }
	printf("\n");//move on to the next line
	tmp = head;//reset tmp to walk down again
	while(tmp != NULL)
	{//print the value
		if(tmp->num == '0')
			printf("║%s   ║ ","10");
		else
			printf("║%c    ║ ",tmp->num);
		tmp=tmp->next;
	}
	printf("\n");
	for(int h=0;h<2;h++)
	{//determine the amount of middle parts to print
		for(int w=0;w<count;w++)
		{//print the cards in a row
			printf("║     ║ ");
		}
		printf("\n");
	}
	tmp = head;
	while(tmp != NULL)
	{//prints the suit
		printf("║    %c║ ",tmp->suit);
		tmp=tmp->next;
	}
	printf("\n");
	for(int i=0;i<count;i++)
	{//prints the bottoms of the cards
		printf("╚═════╝ ");
	}
	printf("\n");//move on to the next line
	return;
}

void printHeader(int *score)
{//prints the pretty colorful header
	printf("\n");
	printf("\033[93m""-----------------------------------------------------------------------\n""\033[0m");
	printf("\033[93m""'||''|.   '||                  '||         ||                 '||      \n""\033[0m");
	printf("\033[93m"" ||   ||   ||   ....     ....   ||  ..    ...  ....     ....   ||  ..  \n""\033[0m");
	printf("\033[93m"" ||'''|.   ||  '' .||  .|   ''  || .'      || '' .||  .|   ''  || .'   \n""\033[0m");
	printf("\033[93m"" ||    ||  ||  .|' ||  ||       ||'|.      || .|' ||  ||       ||'|.   \n""\033[0m");
	printf("\033[93m"".||...|'  .||. '|..'|'  '|...' .||. ||.    || '|..'|'  '|...' .||. ||. \n""\033[0m");
	printf("\033[93m""                                        .. |'                          \n""\033[0m");
	printf("\033[93m""            ~SPADE OF SPADES~             ''     Christoper Loutsch    \n""\033[0m");
	printf("\033[93m""_______________________________________________________________________\n""\033[0m");
	printf("Your total games score: %d\n",*score);
	return;
}
