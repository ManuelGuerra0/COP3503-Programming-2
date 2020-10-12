//
//  BlackJack.h
//  BlackJack
//
//  Created by Jacob Rush, Chris Hoyek, Johncarlo Cerna, Andy Jean-Baptiste, Melanie Lo, Manuel Guerra, and Hyung Ho (Jay) Chun.


#include <iostream>
#include <cstdio>
#include <iostream>
#include <vector> //use for vectors
#include <string> //strings
#include <stdlib.h> //allows access to srand and rand
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

#ifndef BlackJack_h
#define BlackJack_h
class Card
{
public:
    Card(char, int);
    int getRealValue();
    string getSuit();
    string setSuit(int);
    int setRealValue(char);
    void displayCard();
    string setFaceValue(char);
    string getFaceValue();

private:
    string faceValue;
    int realValue;
    string suit;


};

class Deck{
private:
    vector<Card*> deck;
    vector<Card*> discard;
    Card* cardDrawn;

public:
    Deck();
    void shuffleDeck();
    void createDeck();
    void discardCard(string, string);
    Card drawCard();

};

class PlayerHand: public Deck{

private:
    //whatever type Card is, replace it.
    vector<Card> hand;
    vector<Card> discardedHand;
    int handScore;

public:
    //Replace Card with whatever type our draw method will return.
    void turnOne(Card, Card);
    void displayHand();
    void displayDealerHand();
    void drawCard(Card);
    //void splitCard();
    void setHandScore();
    void discardHand();
    int getHandScore();

};


#endif /* BlackJack_h */
