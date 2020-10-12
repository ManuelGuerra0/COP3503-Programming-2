//
//  main.cpp
//  BlackJack
//
//  Created by Jacob Rush, Chris Hoyek, Johncarlo Cerna, Andy Jean-Baptiste, Melanie Lo, Manuel Guerra, and Hyung Ho (Jay) Chun.

#include <iostream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <limits>
#include <iomanip>
#include <algorithm>
#include "BlackJack.h"
using namespace std;


//constructor to create each card
Card::Card(char faceV, int suitNumber){
    faceValue = setFaceValue(faceV);
    realValue = setRealValue(faceV);
    suit = setSuit(suitNumber);
}
//converting the face value into a real point value to calculate how close we are to 21
int Card::setRealValue(char faceV){
    int real = 0;
    switch(faceV){
        case '1': real = 1; break;
        case '2': real = 2; break;
        case '3': real = 3; break;
        case '4': real = 4; break;
        case '5': real = 5; break;
        case '6': real = 6; break;
        case '7': real = 7; break;
        case '8': real = 8; break;
        case '9': real = 9; break;
        case 'T': real = 10; break;
        case 'J': real = 10; break;
        case 'Q': real = 10; break;
        case 'K': real = 10; break;
        case 'A': real = 11; break; //Ace will be a 1 or 11 depending on player's hand score.

    }
    realValue = real;
    return real;

}
//method to just retrieve the face value
int Card::getRealValue(){
    return realValue;
}
//converts our suit number into an actual suit
string Card::setSuit(int suitNumber){
    switch(suitNumber){
        default: return "♣";
        case 0: return "♣"; //Clubs
        case 1: return "♦"; //Diamonds
        case 2: return "♠"; //Spades
        case 3: return "♥"; //Hearts
    }

}
//method to retrieve the suit
string Card::getSuit(){
    return suit;
}
//set the face value to the actual name of the face value;
string Card::setFaceValue(char faceV){
    switch(faceV){
        case '2': return "2";
        case '3': return "3";
        case '4': return "4";
        case '5': return "5";
        case '6': return "6";
        case '7': return "7";
        case '8': return "8";
        case '9': return "9";
        case 'T': return "T"; //T stands for 10
        case 'J': return "J";
        case 'Q': return "Q";
        case 'K': return "K";
        case 'A': return "A";
        default: return "Wrong Card";
    }
}
string Card::getFaceValue(){
    return faceValue; //returns the face value of the card
}
//displays the card
void Card::displayCard(){
    if(faceValue.length() == 1){
        cout << "┌─────┐" << endl <<
             "│" << faceValue << "    │" << endl <<
             "│  "<< suit << "  │" << endl <<
             "│    " << faceValue << "│" << endl <<
             "└─────┘" << endl;
    }
    else{
        cout << "┌─────┐" << endl <<
             "│" << faceValue << "   │" << endl <<
             "│  "<< suit << "  │" << endl <<
             "│   " << faceValue << "│" << endl <<
             "└─────┘" << endl;

    }

}

Deck::Deck(){
    createDeck();
    shuffleDeck();
}
//creates a new deck of 4 different suits, 13 cards in each suit.
void Deck::createDeck(){
    char cardValue = '2';
    for(int suitNumber = 0; suitNumber < 4; suitNumber++){
        for(int i = 0; i < 13; i++){
            switch(i){
                case 0: cardValue = '2'; break;
                case 1: cardValue = '3'; break;
                case 2: cardValue = '4'; break;
                case 3: cardValue = '5'; break;
                case 4: cardValue = '6'; break;
                case 5: cardValue = '7'; break;
                case 6: cardValue = '8'; break;
                case 7: cardValue = '9'; break;
                    //t = 10, J = Jack, Q = Queen, K = King, A = Ace
                case 8: cardValue = 'T'; break;
                case 9: cardValue = 'J'; break;
                case 10: cardValue = 'Q'; break;
                case 11: cardValue = 'K'; break;
                case 12: cardValue = 'A'; break;
            }
            deck.push_back(new Card(cardValue, suitNumber));

        }
    }

}

void Deck:: shuffleDeck(){
    srand(time(0)); //changes the seed for srand and rand for random shuffles every time
    int randomShuffle = rand() % 100; //randomly decides how many times to shuffle
    //check to see if our deck is empty
    if(deck.empty()){
        cout << "We have run out of cards. Reshuffling." << endl;
        createDeck();
        random_shuffle(deck.begin(), deck.end());
        //clear our discard pile after it has been shuffled into our deck
        while(!discard.empty()){
            discard.pop_back();
        }
    }
    //shuffle normally
    for(int i = 0; i < randomShuffle; i++){
        random_shuffle(deck.begin(), deck.end()); //two layers of chaos. Shuffles the deck randomly for a random amount of times.
    }
}

Card Deck::drawCard(){
    //check to see if deck is empty. If it is, shuffle it.
    if(deck.empty()){
        cout << "We have run out of cards. Reshuffling." << endl;
        createDeck();
        shuffleDeck();
    }
    //placeholder for card drawn
    cardDrawn = deck.back();
    deck.pop_back();
    return *cardDrawn;
}
//discarding a card pushes it to our discard pile
void Deck::discardCard(string suit, string faceValue){
    int suitNumber;
    char face = faceValue[0];
    if(suit == "♣") suitNumber = 0;
    else if(suit == "♦") suitNumber = 1;
    else if(suit == "♠") suitNumber = 2;
    else if(suit == "♥") suitNumber  = 3;
    discard.push_back(new Card(suitNumber, face)); //discards the card

}

//easy turn one method. Could always just delete this and run drawCard twice instead
void PlayerHand::turnOne(Card card1, Card card2){
    hand.push_back(card1);
    hand.push_back(card2);
}

void PlayerHand::drawCard(Card card){
    //placeholder for the displayCard method
    card.displayCard();

    hand.push_back(card);
}

void PlayerHand::discardHand(){
    //add each card in a hand to the discard vector
    for(int i = 0; i < hand.size(); i++){
        discardCard(hand[i].getSuit(), hand[i].getFaceValue());
    }
    //clear out the current hand vector
    while(!hand.empty()){
        hand.pop_back();
    }
}

void PlayerHand::displayHand(){
    int handSize = hand.size();

    //.displayCard is a placeholder

    //hand[i].displayCard();
    for(int i = handSize - 1; i >= 0; i--){
        cout << "┌─────┐ ";
    }
    cout << endl;
    for(int i = handSize - 1; i >= 0; i--){
        cout << "│" << hand[i].getFaceValue() << "    │ ";
    }
    cout << endl;
    for(int i = handSize - 1; i >= 0; i--){
        cout << "│  "<< hand[i].getSuit() << "  │ ";
    }
    cout << endl;
    for(int i = handSize - 1; i >= 0; i--){
        cout << "│    " << hand[i].getFaceValue() << "│ ";
    }
    cout << endl;
    for(int i = handSize - 1; i >= 0; i--){
        cout << "└─────┘ ";
    }
    cout << endl;

}

void PlayerHand::displayDealerHand(){
    //we want this to display everything but the first card, because you don't see the dealers first card
    //for(size_t i = (hand.size() -1); i > 0; i--){
    //(hand[i].displayCard());

    //}
    cout << "┌─────┐ ";
    for(size_t i = (hand.size() -1); i > 0; i--){
        cout << "┌─────┐ ";
    }
    cout << endl;
    cout << "│     │ ";
    for(size_t i = (hand.size() -1); i > 0; i--){
        cout << "│" << hand[i].getFaceValue() << "    │ ";
    }
    cout << endl;
    cout << "│     │ ";
    for(size_t i = (hand.size() -1); i > 0; i--){
        cout << "│  "<< hand[i].getSuit() << "  │ ";
    }
    cout << endl;
    cout << "│     │ ";
    for(size_t i = (hand.size() -1); i > 0; i--){
        cout << "│    " << hand[i].getFaceValue() << "│ ";
    }
    cout << endl;
    cout << "└─────┘ ";
    for(size_t i = (hand.size() -1); i > 0; i--){
        cout << "└─────┘ ";
    }
    cout << endl;
}
//add up the total real value of the cards
void PlayerHand::setHandScore(){
    bool ifAce = false;
    //reset the value of handscore each time we run this
    handScore = 0;
    for(int i = 0; i < hand.size(); i++){
        handScore += hand[i].getRealValue();
    }
    if(handScore > 21 && !ifAce){
        for(int j = 0; j < hand.size(); j++){
            if(hand[j].getFaceValue() == "A"){
                handScore -=10;
                ifAce = true;
            }
        }
    }
}

int PlayerHand::getHandScore(){
    return handScore; //returns the score of your hand
}


bool welcome(){
    string key;
    cout <<
         "          ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄       ▄▄  ▄▄▄▄▄▄▄▄▄▄▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄      " << endl << //for best results, play with a maximized window
         "         ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌     ▐░░▌▐░░░░░░░░░░░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌     " << endl <<
         "         ▐░▌       ▐░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌   ▐░▐░▌▐░█▀▀▀▀▀▀▀▀▀            ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌     " << endl <<
         "         ▐░▌       ▐░▌▐░▌          ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌▐░▌ ▐░▌▐░▌▐░▌                         ▐░▌     ▐░▌       ▐░▌     " << endl <<
         "         ▐░▌   ▄   ▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌ ▐░▐░▌ ▐░▌▐░█▄▄▄▄▄▄▄▄▄                ▐░▌     ▐░▌       ▐░▌     " << endl <<
         "         ▐░▌  ▐░▌  ▐░▌▐░░░░░░░░░░░▌▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌  ▐░▌  ▐░▌▐░░░░░░░░░░░▌               ▐░▌     ▐░▌       ▐░▌     " << endl <<
         "         ▐░▌ ▐░▌░▌ ▐░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌   ▀   ▐░▌▐░█▀▀▀▀▀▀▀▀▀                ▐░▌     ▐░▌       ▐░▌     " << endl <<
         "         ▐░▌▐░▌ ▐░▌▐░▌▐░▌          ▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌                         ▐░▌     ▐░▌       ▐░▌     " << endl <<
         "         ▐░▌░▌   ▐░▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄▄▄                ▐░▌     ▐░█▄▄▄▄▄▄▄█░▌     " << endl <<
         "         ▐░░▌     ▐░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌               ▐░▌     ▐░░░░░░░░░░░▌     " << endl <<
         "          ▀▀       ▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀                 ▀       ▀▀▀▀▀▀▀▀▀▀▀      " << endl <<
         "                                                                                                                                             " << endl <<
         "                    ▄▄▄▄▄▄▄▄▄▄   ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄    ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄    ▄                " << endl <<
         "                   ▐░░░░░░░░░░▌ ▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌               " << endl <<
         "                   ▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░▌ ▐░▌  ▀▀▀▀▀█░█▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░▌ ▐░▌                " << endl <<
         "                   ▐░▌       ▐░▌▐░▌          ▐░▌       ▐░▌▐░▌          ▐░▌▐░▌        ▐░▌    ▐░▌       ▐░▌▐░▌          ▐░▌▐░▌                 " << endl <<
         "                   ▐░█▄▄▄▄▄▄▄█░▌▐░▌          ▐░█▄▄▄▄▄▄▄█░▌▐░▌          ▐░▌░▌         ▐░▌    ▐░█▄▄▄▄▄▄▄█░▌▐░▌          ▐░▌░▌                  " << endl <<
         "                   ▐░░░░░░░░░░▌ ▐░▌          ▐░░░░░░░░░░░▌▐░▌          ▐░░▌          ▐░▌    ▐░░░░░░░░░░░▌▐░▌          ▐░░▌                   " << endl <<
         "                   ▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░▌░▌         ▐░▌    ▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░▌░▌                  " << endl <<
         "                   ▐░▌       ▐░▌▐░▌          ▐░▌       ▐░▌▐░▌          ▐░▌▐░▌        ▐░▌    ▐░▌       ▐░▌▐░▌          ▐░▌▐░▌                 " << endl <<
         "                   ▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌ ▐░▌  ▄▄▄▄▄█░▌    ▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌ ▐░▌                " << endl <<
         "                   ▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌▐░░░░░░░▌    ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌               " << endl <<
         "                    ▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀    ▀  ▀▀▀▀▀▀▀      ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀    ▀                " << endl <<
         "            _____                      _ _      _                _   _ _   _                              _    _                             " << endl <<
         "           |_   _|_   _  _ __    ___  ( | )___ | |_  __ _  _ __ | |_( | ) | |_  ___     ___  ___   _ __  | |_ (_) _ __   _   _   ___         " << endl <<
         "             | | | | | || '_ \\  / _ \\  V V/ __|| __|/ _` || '__|| __|V V  | __|/ _ \\   / __|/ _ \\ | '_ \\ | __|| || '_ \\ | | | | / _ \\ " << endl <<
         "             | | | |_| || |_) ||  __/     \\__ \\| |_| (_| || |   | |_      | |_| (_) | | (__| (_) || | | || |_ | || | | || |_| ||  __/      " << endl <<
         "             |_|  \\__, || .__/  \\___|     |___/ \\__|\\__,_||_|    \\__|      \\__|\\___/   \\___|\\___/ |_| |_| \\__||_||_| |_| \\__,_| \\___|" << endl <<
         "                  |___/ |_|        " << endl << endl << endl << endl << endl <<
         "                                 If the above text is not compatible with your computer, type \"start\" to begin." << endl;

    while (key != "start"){ //type start or start over
        cin >> key;
        if (key == "start"){
            return true;
        }else{
            cout << "Invalid input. Please try again." << endl;
        }
    }
    return false;
}

bool rules(){
    string key;
    cout << endl << endl << endl << endl <<
         "                           _   _                                       _    _                          _               \n"
                 "                          | | | |  ___  _ __  ___    __ _  _ __  ___  | |_ | |__    ___   _ __  _   _ | |  ___  ___  _ \n"
                 "                          | |_| | / _ \\| '__|/ _ \\  / _` || '__|/ _ \\ | __|| '_ \\  / _ \\ | '__|| | | || | / _ \\/ __|(_)\n"
                 "                          |  _  ||  __/| |  |  __/ | (_| || |  |  __/ | |_ | | | ||  __/ | |   | |_| || ||  __/\\__ \\ _ \n"
                 "                          |_| |_| \\___||_|   \\___|  \\__,_||_|   \\___|  \\__||_| |_| \\___| |_|    \\__,_||_| \\___||___/(_)\n" << endl << endl <<
         "BlackJack is a very simple game. The goal is to get total your cards to 21 or beat the dealer. " << endl <<
         "If you go over 21, you automatically lose/bust. If you have a lower score than the dealer, you lose. " << endl <<
         "You will start out with 10 points. Getting 21: +5 points. Beating the dealer: +3 points. " << endl <<
         "Forfeiting/Folding: -2 points. Losing to dealer: -3 points. Busting: -5 points." << endl <<
         "If you hit 0 points or less, you will lose the game. You can quit the game whenever you like and see your final score." << endl <<
         "Each card will yield the face value, except Kings, Queens, and Jacks are 10 score points. "<< endl <<
         "An Ace is 11 until you reach over 21, then it will become a 1"<< endl <<
         "You may choose to 'Stand' which will compare your current hand to the dealers, and finish the round. " << endl <<
         "S = Spades, H = Hearts, C = Clubs, D = Diamonds. T = 10, K = King, Q = Queen, J = Jack." << endl <<
         "Make sure to have fun!!!" << endl << endl <<
         "                     _____                      _ _      _                _   _ _   _           _                   _                        " << endl <<
         "                    |_   _|_   _  _ __    ___  ( | )___ | |_  __ _  _ __ | |_( | ) | |_  ___   | |__    ___   __ _ (_) _ __                  " << endl <<
         "                      | | | | | || '_ \\  / _ \\  V V/ __|| __|/ _` || '__|| __|V V  | __|/ _ \\  | '_ \\  / _ \\ / _` || || '_ \\           " << endl <<
         "                      | | | |_| || |_) ||  __/     \\__ \\| |_| (_| || |   | |_      | |_| (_) | | |_) ||  __/| (_| || || | | |              " << endl <<
         "                      |_|  \\__, || .__/  \\___|     |___/ \\__|\\__,_||_|    \\__|      \\__|\\___/  |_.__/  \\___| \\__, ||_||_| |_|       " << endl <<
         "                           |___/ |_|                                                                         |___/                           " << endl;
    while (key != "start"){
        cin >> key;
        if (key == "start"){
            return true;
        }else{
            cout << "Invalid input. Please try again." << endl;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    int points = 10; //initializing
    int dealerScore = 0;
    int menuChoice = 0;
    string garbage = "";
    Deck* deck = new Deck;
    PlayerHand* player1 = new PlayerHand;
    PlayerHand* dealer = new PlayerHand;
    player1->turnOne(deck->drawCard(), deck -> drawCard());
    dealer ->turnOne(deck->drawCard(), deck -> drawCard());
    welcome();
    rules();
    cout << "Enter anything to check your hand" << endl;
    cin >> garbage;
    player1 -> displayHand();
    cout << "Enter anything to check dealer's hand" << endl;
    cin >> garbage;
    dealer -> displayDealerHand(); //displays each hand

    while(menuChoice != 9){
        cout << "Please select a menu choice" << endl;
        cout << "1. Check Hand" << endl;
        cout << "2. Hit me!" << endl;
        cout << "3. Stand" << endl;
        cout << "4. Forfeit" << endl;
        cout << "5. Check Dealer's Hand" << endl;
        cout << "6. Check Hand Value" << endl;
        cout << "7. Consult Henry The Helper" << endl;
        cout << "8. Check Total Points" << endl;
        cout << "9. End game" << endl;
        cin >> menuChoice;
        if(menuChoice > 0 && menuChoice < 10){
            switch(menuChoice){
                case 1: player1-> displayHand(); break; //display your hand
                case 2: {
                    cout << "You draw the following card: " << endl; //take a card from the deck.
                    player1 -> drawCard(deck -> drawCard());
                    dealer -> setHandScore();
                    player1 -> setHandScore();
                    if(dealer -> getHandScore() < 17){
                        cout << "Dealer draws the following card: " << endl; //the dealer will also take a card...
                        dealer -> drawCard(deck -> drawCard());
                    }
                    else{
                        cout << "The dealer does not draw, because he has a score of 17 or above" << endl; //unless his score is above a 17.
                    }
                    if(player1 -> getHandScore() > 21){ //if your hand is above 21, you bust and lose 5 points.
                        cout << "You bust! -5 points." << endl;;
                        points -= 5;
                        if(points <= 0){
                            cout << "You have lost all of your points. Game over." << endl; //if your points go below zero, you lose!
                            exit(0);
                        }
                        cout << "Restarting a new round" << endl;
                        player1->discardHand(); //discard hands
                        dealer -> discardHand();
                        player1->turnOne(deck->drawCard(), deck -> drawCard()); //get two cards.
                        dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                        cout << "Enter anything to check your hand" << endl;
                        cin >> garbage;
                        player1 -> displayHand();
                        cout << "Enter anything to check dealer's hand" << endl;
                        cin >> garbage;
                        dealer -> displayDealerHand();
                    }
                    if(player1 -> getHandScore() == 21){ //if you get a 21, you win automatically
                        cout << "You win! You got 21! +5 points!" << endl;
                        points += 5;
                        player1->discardHand();
                        dealer -> discardHand();
                        cout << "Restarting a new round" << endl;
                        player1->turnOne(deck->drawCard(), deck -> drawCard());
                        dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                        cout << "Enter anything to check your hand" << endl;
                        cin >> garbage;
                        player1 -> displayHand();
                        cout << "Enter anything to check dealer's hand" << endl;
                        cin >> garbage;
                        dealer -> displayDealerHand();
                    }
                    dealer -> setHandScore();
                    if(dealer -> getHandScore() > 21){
                        dealerScore = 0;
                    }
                    else{
                        dealerScore = dealer -> getHandScore();
                    }
                    break;

                }
                case 3: {
                    player1 -> setHandScore();
                    dealer -> setHandScore();
                    cout << "The dealer has a score of " << dealer -> getHandScore() << endl; //check your score and the dealer's score.
                    cout << "You have a score of " << player1 -> getHandScore() << endl;
                    if(player1->getHandScore()==21){
                        cout << "You win! You got 21! +5 points!" << endl;
                        points += 5;
                        player1->discardHand();
                        dealer -> discardHand();
                        cout << "Restarting a new round" << endl;
                        player1->turnOne(deck->drawCard(), deck -> drawCard());
                        dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                        cout << "Enter anything to check your hand" << endl;
                        cin >> garbage;
                        player1 -> displayHand();
                        cout << "Enter anything to check dealer's hand" << endl;
                        cin >> garbage;
                        dealer -> displayDealerHand();
                    }
                    if(player1 -> getHandScore() > dealer -> getHandScore()|| dealer->getHandScore() > 21){ // if the dealer busts or your points are higher than the dealer's, you win.
                        cout << "You win! +3 points" << endl;
                        points += 3;
                        player1->discardHand();
                        dealer -> discardHand();
                        cout << "Restarting a new round" << endl;
                        player1->turnOne(deck->drawCard(), deck -> drawCard());
                        dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                        cout << "Enter anything to check your hand" << endl;
                        cin >> garbage;
                        player1 -> displayHand();
                        cout << "Enter anything to check dealer's hand" << endl;
                        cin >> garbage;
                        dealer -> displayDealerHand();
                    }
                    else if(player1 -> getHandScore() == dealer -> getHandScore()){ //if your scores are the same, no points are awarded.
                        cout << "Draw! No points awarded." << endl;
                        player1->discardHand();
                        dealer -> discardHand();
                        cout << "Restarting a new round" << endl;
                        player1->turnOne(deck->drawCard(), deck -> drawCard());
                        dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                        cout << "Enter anything to check your hand" << endl;
                        cin >> garbage;
                        player1 -> displayHand();
                        cout << "Enter anything to check dealer's hand" << endl;
                        cin >> garbage;
                        dealer -> displayDealerHand();
                    }
                    else{
                        cout << "You lose! -3 points." << endl; //if the dealer has a higher score then yours, you lose 3 points.
                        points -= 3;
                        if(points <= 0){
                            cout << "You have lost all of your points. Game over." << endl;
                            exit(0);
                        }
                        player1->discardHand();
                        dealer -> discardHand();
                        cout << "Restarting a new round" << endl;
                        player1->turnOne(deck->drawCard(), deck -> drawCard());
                        dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                        cout << "Enter anything to check your hand" << endl;
                        cin >> garbage;
                        player1 -> displayHand();
                        cout << "Enter anything to check dealer's hand" << endl;
                        cin >> garbage;
                        dealer -> displayDealerHand();
                    }
                    break;
                }
                case 4: {
                    cout << "You forfeited! - 2 points." << endl; //if you decide to forfeit the match, you lose 2 points.
                    points -=2;
                    if(points <= 0){
                        cout << "You have lost all of your points. Game over." << endl;
                        exit(0);
                    }
                    player1->discardHand();
                    dealer -> discardHand();
                    cout << "Restarting a new round" << endl;
                    player1->turnOne(deck->drawCard(), deck -> drawCard());
                    dealer ->turnOne(deck->drawCard(), deck -> drawCard());
                    cout << "Enter anything to check your hand" << endl;
                    cin >> garbage;
                    player1 -> displayHand();
                    cout << "Enter anything to check dealer's hand" << endl;
                    cin >> garbage;
                    dealer -> displayDealerHand();
                    break;
                }
                case 5:{
                    dealer -> displayDealerHand(); //shows a card from the dealer's hand
                    break;
                }
                case 6:{
                    player1 -> setHandScore();
                    cout << "Your current hand yields a value of " << player1 ->getHandScore() << endl; //checks your points.
                    break;
                }
                case 7:{ //asks for the help of henry the helper. He'll help you make a decision if you're stuck.
                    player1 -> setHandScore();
                    if (player1 ->getHandScore() == 15 || player1 ->getHandScore() == 16){ //since 15 and 16 are scary spots, forfeiting is the best option.
                        cout << "Henry Says: You're in a tricky spot. I'd forfeit to minimize losses." << endl;
                    }else if (player1 ->getHandScore() < 15){ //if you're below 15, he'll recommend you hit.
                        cout << "Henry Says: You should hit!" << endl;
                    }else{ //if you're above 16, he'll tell you to stand.
                        cout << "Henry Says: You should stand!" << endl;
                    }
                    break;
                }
                case 8:{
                    cout << "You currently have " << points << " points." << endl; //tells you your available points.
                    break;
                }
                case 9:{
                    cout << "You have finished the game! You have " << points << " points." << endl; //when you exit, this will tell you your remaining points.
                    exit(0);
                }
            }
        }else{
            cout << "Not a valid menu choice. Please input a new menu choice: " << endl;
            //stops infinite loop
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}
