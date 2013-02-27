#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

class Card
{
public:
   enum Suit{clubs, diamonds, hearts, spades};
   enum State{deleted, active};
   Card(char value = 'A', Suit suit = spades);
   string toString();
   bool set(char value = 'A', Suit suit = spades);
   bool SetState(State state);
   State GetState() {return this->state;}
   Suit GetSuit() {return suit;}
   char GetValue() {return value;}
   bool GetErrorFlag() {return this->errorFlag;}
   bool equals(Card card);

   int compareTo(Card &other);

   static void setrankingOrder(char valueOrderArr[], Card::Suit suitOrderArr[],
      int numCardsInOrderingArray);
   static int getSuitRank(Card::Suit st);
   static int getValueRank(char val);
   static void arraySort(Card array[], int arraySize);

private:
   char value;
   Suit suit;
   State state;
   bool errorFlag;

   static char valueRanks[14];
   static Card::Suit suitRanks[4];
   static int numValsInOrderingArray;

   static bool floatLargestToTop(Card array[], int top); 
   static void swap(Card &a, Card &b);

};

char Card::valueRanks[14] = {'2', '3', '4', '5', '6', '7', '8', '9', 
	'T', 'J', 'Q', 'K', 'A'};
enum Card::Suit Card::suitRanks[4] = {Card::clubs, Card::diamonds, Card::hearts, Card::spades};
int Card::numValsInOrderingArray =  13;
class Hand
{
public:

   static const int MAX_CARDS = 50;
   Hand();
   void resetHand();
   bool takeCard(Card card);
   Card playCard();
   string toString();
   int GetnumCards() {return this->numCards;}
   Card inspectCard(int k);
   
   void sort();

private:

   Card myCards[MAX_CARDS];
   int numCards;

};

class Deck
{
public:
   static const int MAX_CARDS = 324;
   static Card masterPack[52];

   Deck(int numPacks = 1);
   void init(int numPacks = 1);
   void shuffle();
   Card dealCard();
   bool removeCard(Card card);
   bool addCard(Card card);
   int GetnumPacks() {return this->numPacks;}
   int GettopCard() {return this->topCard;}
   Card inspectCard(int k);
   static void allocateMasterPack();
   string toString();

   void sort();

private:
   Card cards[MAX_CARDS];
   int topCard;
   int numPacks;
};
Card Deck::masterPack[52];

class CardGameFramework
{
public:
   const static int MAX_PACKS = 6;
   const static int MAX_PLAYERS = 12;
   const static int MAX_JOKERS = 12;
   const static int MAX_UNUSED = 52;
   const static int MAX_CARDPERHAND = 52;

private:
   int numPlayers;
   int numPacks; 
   int numJokersPerPack;         
   int numUnusedCardsPerPack;    
   int numCardsPerHand;          
   Deck deck;                                               
   Hand hand[MAX_PLAYERS];       
   Card UnusedCardsPerPack[52];                                           
public:
   CardGameFramework( int numPacks = 1, int numJokersPerPack = 0,
      int numUnusedCardsPerPack = 0, Card UnusedCardsPerPack[] = NULL,
      int numPlayers = 4, int numCardsPerHand = 13);
   void newGame();
   bool deal();
   Hand getHand(int k);
   Card getCardfromDeck(); 
   int getNumCardsRemainingInDeck();
   int getNumPlayers() {return this->numPlayers;}
   void sortHands();
};

Card generateRandomCard(bool fixedSequence = true);

int main() //CardGameFramework Test
{
   srand(time(NULL));
   Card Card1('2', Card::spades), Card2('2', Card::clubs), 
      Card3('2', Card::diamonds), Card4('2', Card::hearts);
   Card array[] = {Card1, Card2, Card3, Card4};

   CardGameFramework Game1(1, 0, 0, array, 4, 13);
   CardGameFramework Game2(2, 1, 0, array, 6, 20);
   CardGameFramework Game3(2, 1, 4, array, 5, 10);
   
   cout << "=======================Game 1==============================" 
      << endl << endl;

   Game1.deal();
   for (int i = 0; i < Game1.getNumPlayers() ; i++)
   {
      cout << "player #" << i << " --------------------------------------"
         << endl << Game1.getHand(i).toString() << endl;
   }

   cout << endl << "Number of Cards Remaining:" << endl;

   for(int k = 0; k < 324; k++)
   {
      cout << Game1.getCardfromDeck().toString() << endl;
      if(Game1.getNumCardsRemainingInDeck() == 0)
         break;   
   }

   cout << "========================Game 2=============================" 
      << endl << endl;

   Game2.deal();
   for (int i = 0; i < Game2.getNumPlayers() ; i++)
   {
      cout << "player #" << i << " --------------------------------------"
         << endl << Game2.getHand(i).toString() << endl;
   }

   cout << endl << "Number of Cards Remaining:" << endl;

   for(int k = 0; k < 324; k++)
   {
      cout << Game2.getCardfromDeck().toString() << endl;
      if(Game2.getNumCardsRemainingInDeck() == 0)
         break;   
   }

   cout << "=======================Game 3==============================" 
      << endl << endl;

   Game3.deal();
   for (int i = 0; i < Game3.getNumPlayers() ; i++)
   {
      cout << "player #" << i << " --------------------------------------"
         << endl << Game3.getHand(i).toString() << endl;
   }

   cout << endl << "Number of Cards Remaining:" << endl;

   for(int k = 0; k < 324; k++)
   {
      cout << Game3.getCardfromDeck().toString() << endl;
      if(Game3.getNumCardsRemainingInDeck() == 0)
         break;
   }

   return(0);
}

// Card methods
Card::Card(char value, Suit suit)
{
   set(value, suit);
   SetState(active);
}

bool Card::set(char value, Suit suit)
{
   char UpCase;
   UpCase = toupper((int)value);
   
   if(UpCase == 'A' || UpCase == 'K' || UpCase == 'Q' || UpCase == 'J' ||
      UpCase == 'X' || UpCase == 'T' || (UpCase >= '2' && UpCase <= '9'))
   {
      state = active;
      this->suit = suit;
      this->value = UpCase;
      errorFlag = false;
      return true;
   }
   else
   {
      errorFlag = true;
      return false;
   }
}

bool Card::SetState(State state)
{
   if(state == active)
   {
      this->state = state;
      return true;
   }
   else if (state == deleted)
   {
      this->state = state;
      return false;
   }
}

bool Card::equals(Card card)
{
   if(this->value == card.value && 
      this->suit == card.suit && 
      this->errorFlag == card.errorFlag
      && this->state == card.state)
      return true;
   else
      return false;
}

string Card::toString()
{
   string deletedout = "[deleted]";
   string invalidout = "[invalid]";
   string validout;
   
   if(state == deleted)
   {
      return deletedout;
   }
   else if(value == 'X')
   {
      if (suit == spades)
         validout += "Joker # 1";
      else if (suit == diamonds)
         validout += "Joker # 2";
      else if (suit == hearts)
         validout += "Joker # 3";
      else if (suit == clubs)
         validout += "Joker # 4";
      return validout;
   }
   else if(value == 'A' || value == 'K' || value == 'Q' || value == 'J' ||
      value == 'T' || (value >= '2' && value <= '9'))
   {
      char validVal[2];
      validVal[0] = value;
      validVal[1] = '\0';
      validout = string(validVal);

      if (suit == spades)
         validout += " of Spades";
      else if (suit == hearts)
         validout += " of Hearts";
      else if (suit == diamonds)
         validout += " of Diamonds";
      else if (suit == clubs)
         validout += " of Clubs";
      return validout;
   }
   else if(errorFlag == true)
   {
      return invalidout;
   }
}

void Card::swap(Card &a, Card &b)
{
   Card swap;
   swap = a;
   a = b;
   b = swap;
}

int Card::compareTo(Card &other)
{
   int thisValpos, otherValpos, thisStpos, otherStpos, compareVal;

   thisValpos = getValueRank(this->GetValue());
   otherValpos = getValueRank(other.GetValue());
   thisStpos = getSuitRank(this->GetSuit());
   otherStpos = getSuitRank(other.GetSuit());

   compareVal = (thisValpos + thisStpos) - (otherValpos + otherStpos);
   return compareVal;
}

int Card::getSuitRank(Card::Suit st)
{
   int StPos;
   for (int j = 0; j < 4; j++)
      if(suitRanks[j] == st)
         StPos = j;

   return StPos;
}

int Card::getValueRank(char val)
{
   int ValPos;

   for(int k = 0; k < numValsInOrderingArray; k++)
      if(valueRanks[k] == val)
         ValPos = k*4;

   return ValPos;
}

void Card::setrankingOrder(char valueOrderArr[], Card::Suit suitOrderArr[],
      int numCardsInOrderingArray)
{
   numValsInOrderingArray = numCardsInOrderingArray;
   for(int k = 0; k<numValsInOrderingArray; k++)
      valueRanks[k] = valueOrderArr[k];
   for(int i = 0; i<4; i++)
      suitRanks[i] = suitOrderArr[i];
}

void Card::arraySort(Card array[], int arraySize)
{
   for (int i = 0; i < arraySize; i++)
      if(!floatLargestToTop(array, arraySize-1-i))
         return;
}

bool Card::floatLargestToTop(Card array[], int top)
{
   bool change = false;
   
   for (int k = 0; k < top; k++)
   {
      if(array[k].compareTo(array[k+1]) > 0)
      {
         swap(array[k], array[k+1]);
         change = true;
      }
   }

   return change;
}

// Hand methods
 Hand::Hand()
{
   resetHand();
}

void Hand::resetHand()
{
   memset(myCards, 0, sizeof(myCards));
   numCards = 0;
}

bool Hand::takeCard(Card card)
{
   if (numCards >= MAX_CARDS)
      return false;

   myCards[numCards++].set(card.GetValue(), card.GetSuit());
   return true;
}

Card Hand::playCard()
{
   Card errorReturn(0, Card::diamonds);

   if(numCards<=MAX_CARDS && numCards>=0)
   {
      Card playcard;
      playcard = myCards[numCards-1];
      myCards[numCards-1] = 0;
      numCards--;
      return playcard;
   }
   else
      return errorReturn;
}

string Hand::toString()
{
   string retString = "( ";
   for (int k=0; k<numCards; k++)
   {
      retString += myCards[k].toString();
      if (k < numCards - 1)
         retString += ", ";
   }
   retString += " )";
   return retString;
}

Card Hand::inspectCard(int k)
{
   Card errorReturn(0, Card::diamonds);

   if(k >= (numCards) || k < 0)
      return errorReturn;
   else if (k <= (numCards-1) && k >= 0)
      return myCards[k];
 }

void Hand::sort()
{
   Card::arraySort(myCards, numCards);
}
//generateRandomCard method
Card generateRandomCard(bool fixedSequence)
{
   Card deck[52];
   char values[] = {'A', '2', '3', '4', '5', '6', '7', 
      '8', '9', 'T', 'J', 'Q', 'K'};
   char charVal;
   Card::Suit suitVal;

   for(int k = 0; k<4; k++)
      for(int i = 0; i<13; i++)
      {
         charVal = values[i];
         suitVal = Card::Suit(k);
         deck[(k*13)+i] = Card(charVal, suitVal);
      }

   Card retCard;
   static bool firstSequence = true;

   if(firstSequence && !fixedSequence)
   {
      firstSequence = false;
      srand(time( NULL ));
   }
   else if(firstSequence && fixedSequence)
   {
      firstSequence = false;
      srand(0);
   }
   
   retCard = deck[rand() % 51];
   return retCard;
}

// Deck methods
Deck::Deck(int numPacks)
{
   static int allocate = 0;
   topCard = 0;
   if(allocate == 0)
   {
      allocateMasterPack();
      allocate++;
   }
   init(numPacks);
}

void Deck::init(int numPacks)
{
   if (numPacks < 1 || numPacks > 6)
      numPacks = 1;

   for (int j = 0; j < numPacks; j++)
      for (int k = 0; k < 52; k++)
         cards[j*52 + k] = masterPack[k];

   this->numPacks = numPacks;
   topCard = numPacks * 52;
}

void Deck::shuffle()
{
   Card temp;
   int index;
   for (int k = topCard - 1; k > 0; k--)
   {
      index = rand() % (k+1);
      temp = cards[index];
      cards[index] = cards[k];
      cards[k] = temp;
   } 
}

bool Deck::removeCard(Card card)
{
   int numCardsRemoved = 0;
   Card placeHold;

   for(int j = 0; j<MAX_CARDS; j++)
   {
      placeHold = cards[j];

      if(placeHold.equals(card))
      {
         for(int k = j; k < MAX_CARDS; k++)
            cards[k] = cards[k+1];
         numCardsRemoved++;
         topCard--;
      }
   }
   if(numCardsRemoved > 0)
      return true;
   else if(numCardsRemoved == 0)
      return false;
}

bool Deck::addCard(Card card)
{
   int numCards = 0;
   Card placeHold;

   for(int j = 0; j<MAX_CARDS; j++)
   {
      placeHold = cards[j];

      if(placeHold.equals(card))
         numCards++;
   }

   if((topCard + numCards)<MAX_CARDS)
   {
      cards[topCard++] = card;
      return true;
   }
   if((topCard + numCards)>=MAX_CARDS)
   {
      return false;
   }
}

Card Deck::inspectCard(int k)
{
   if(k > (topCard-1) || k < 0)
      return 0;
   else if (k <= (topCard-1) && k >= 0)
      return cards[k];
 }

Card Deck::dealCard()
{
   if(topCard > 0 && topCard <= MAX_CARDS)
   {
      Card dealcard;
      dealcard = cards[topCard-1];
      topCard--;
      return dealcard;
   }
   else
      return 0;
}

string Deck::toString()
{
   string DeckOut = "";
   for (int k=0; k<topCard; k++)
      DeckOut += cards[k].toString() + " / ";
   return DeckOut;
}

void Deck::sort()
{
   Card::arraySort(cards, topCard);
}

void Deck::allocateMasterPack()
{
   char values[] = {'A', '2', '3', '4', '5', '6', '7', 
      '8', '9', 'T', 'J', 'Q', 'K'};
   char charVal;
   Card::Suit suitVal;

   for(int k = 0; k<4; k++)
      for(int i = 0; i<13; i++)
      {
         charVal = values[i];
         suitVal = Card::Suit(k);
         masterPack[(k*13)+i] = Card(charVal, suitVal);
      }
}

//CardGameFramework Methods
CardGameFramework::CardGameFramework( int numPacks, int numJokersPerPack,
   int numUnusedCardsPerPack, Card UnusedCardsPerPack[],
   int numPlayers, int numCardsPerHand)
{

   if(numPacks >=0 && numPacks < MAX_PACKS)
      this->numPacks = numPacks;
   else
      this->numPacks = 1;

   if(numJokersPerPack >= 0 && numJokersPerPack < MAX_JOKERS)
      this->numJokersPerPack = numJokersPerPack;
   else
      this->numJokersPerPack = 0;

   if(numPlayers > 0 && numPlayers < MAX_PLAYERS)
      this->numPlayers = numPlayers;
   else
      this->numPlayers = 4;

   if(numCardsPerHand > 0 && numCardsPerHand < MAX_CARDPERHAND)
      this->numCardsPerHand = numCardsPerHand;
   else
      this->numCardsPerHand = 13;

   if(numUnusedCardsPerPack >= 0 && numUnusedCardsPerPack < MAX_UNUSED)
      this->numUnusedCardsPerPack = numUnusedCardsPerPack;
   else
      this->numUnusedCardsPerPack = 0;

   for(int k = 0; k < numUnusedCardsPerPack; k++)
   {
      if(!UnusedCardsPerPack[k].GetErrorFlag())
         this->UnusedCardsPerPack[k] = UnusedCardsPerPack[k];
      else
      {
         this->numUnusedCardsPerPack = 0;
         this->UnusedCardsPerPack[k] = NULL;
      }
   }
   
   newGame();
}

void CardGameFramework::newGame()
{
   deck.init(numPacks);

   for (int j = 0; j < numPlayers; j++)
      hand[j].resetHand();

   for(int k = 0; k < numJokersPerPack*numPacks; k++)
      deck.addCard(Card('X', Card::spades));
   if(numUnusedCardsPerPack > 0)
      for(int i = 0; i < numUnusedCardsPerPack; i++)
         deck.removeCard(UnusedCardsPerPack[i]);

   deck.shuffle();
}

bool CardGameFramework::deal()
{   

   for(int k = 0; k < numCardsPerHand; k++)
      for(int i = 0; i < numPlayers; i++)
      {
         hand[i].takeCard(deck.dealCard());
         if (deck.GettopCard() == 0)
            break;
      }

   if(deck.GettopCard() > 0)
      return true;
   else if (deck.GettopCard() == 0 && 
      hand[numPlayers-1].GetnumCards() == numCardsPerHand)
      return true;
   else if (deck.GettopCard() == 0 && 
      hand[numPlayers-1].GetnumCards() < numCardsPerHand)
      return false;
}

Card CardGameFramework::getCardfromDeck()
{
   return deck.dealCard();
}

int CardGameFramework::getNumCardsRemainingInDeck()
{
   return deck.GettopCard();
}

Hand CardGameFramework::getHand(int k)
{
   Hand errorReturn;

   if(k >= 0 && k < numPlayers)
      return this->hand[k];
   else
      return errorReturn;
}

void CardGameFramework::sortHands()
{
   for(int k = 0; k < numPlayers; k++)
      hand[k].sort();
}
