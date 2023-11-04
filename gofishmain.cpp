#include"card.h"
#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include <map>


using std::endl;
using std::deque;
using std::cin;
using std::cout;

deque<card*> buildDeck(deque<card*> deck);
bool searchHand(string choice, vector<card*>& hand, vector<card*>& foundCards);
int checkForBooks(vector<card*>& hand, int& bookCount);
string compTurn(vector<card*>& hand, string& lastAskedCard);

vector<card*> myHand, compHand;
vector<card*> foundCards;
vector<card*> deal(vector<card*>);
string lastAskedCard = "";
bool cardFound;

int myRand(int i)
{
    return rand() % i;
}

int main() {

    

    deque<card*> myDeck;
    myDeck = buildDeck(myDeck); //build the deck.




    cout << "Go fish. The game." << endl << endl;
    cout << "Dealing 7 cards to you and the comp." << endl << endl;

    int playerBookCount = 0;
    int compBookCount = 0;
    string bookCheck = "";
    string playerChoice;
    string compChoice;

    for (int i = 0; i < 7 && i < myDeck.size(); i++)//deal hand to player
    {
        myHand.push_back(myDeck.front());
        myDeck.pop_front();

    }

    for (int i = 0; i < 7 && i < myDeck.size(); i++) //deal hand to computer
    {
        compHand.push_back(myDeck.at(i));
        myDeck.pop_front();

    }

   

    while (playerBookCount + compBookCount != 13) { //start game loop

        cout << "Player hand: " << endl;
        for (int i = 0; i < myHand.size(); i++) {
            cout << myHand.at(i)->getFace() << " " << myHand.at(i)->getSuit() << endl; //show player hand
        }

        cout << endl << endl;

        //cout << "Comp hand: " << endl;
        //for (int i = 0; i < compHand.size(); i++) {
        //    cout << compHand.at(i)->getFace() << " " << compHand.at(i)->getSuit() << endl; //show player hand
        //}

        cout << endl << endl;

        
        cout << "Player turn. " << endl << endl;
        cout << "Ask the comp for a card: (A thru K) " << endl << endl;

        do {                            //loop that repeats when a sucessful choice is made.

            cin >> playerChoice;        //player inputs choice 2 thru A.

            cardFound = (searchHand(playerChoice, compHand, foundCards)); //search the computers hand for desired card(s)

            if (foundCards.size() == 0) {
                cout << "Sorry, comp doesn't have any " << playerChoice << "'s. Go fish." << endl; //player draws card (go fish) if desired card(s) are not in comp's hand
                cout << "You drew a " << myDeck.front()->getFace() << " " << myDeck.front()->getSuit() << endl;
                myHand.push_back(myDeck.front());
                myDeck.pop_front();
            }
            else {
                int count = 0;
                for (int i = 0; i < foundCards.size(); i++) {
                    myHand.push_back(foundCards.at(i));
                    count++;
                }
                if (count == 1) {
                    cout << "Comp gave you its " << foundCards.at(0)->getFace() << "." << endl << "Ask for a different card." << endl;
                }
                else {
                    cout << "Comp gave you " << count << " " << foundCards.at(0)->getFace() << "'s." << endl << "Ask for a different card." << endl; //desired card(s) found and added to player's hand
                }
            }

            foundCards.clear();

        } while (cardFound != false);

        


        if (checkForBooks(myHand, playerBookCount) == 0) {                          //at the end of every turn, check for books (4 of a kind)
            cout << endl << endl << "No new books this turn." << endl << endl;
            cout << endl << endl << "Player score: " << playerBookCount << endl;
            cout << "Comp score: " << compBookCount << endl << endl;
        }
        else {
            checkForBooks(myHand, playerBookCount);
            cout << "You got new books!" << endl;
            cout << "Player score: " << playerBookCount << endl;
            cout << "Comp score: " << compBookCount << endl << endl;
        }



        cout << endl << "Comp's turn. " << endl;

        do {
            compChoice = compTurn(compHand, lastAskedCard);         //creates optimal card choice for comp's turn
            cout << "Comp asks: Do you have any " << compChoice << "'s?" << endl << endl;

            cardFound = (searchHand(compChoice, myHand, foundCards));       //process repeats but for comp

            if (foundCards.size() == 0) {
                cout << "Sorry Comp, I don't have any " << compChoice << "'s. Go fish.";
                compHand.push_back(myDeck.front());
                myDeck.pop_front();
            }
            else {
                int count = 0;
                for (int i = 0; i < foundCards.size(); i++) {
                    compHand.push_back(foundCards.at(i));
                    count++;
                }
                if (count == 1) {
                    cout << "You gave comp your " << count << " " << foundCards.at(0)->getFace() << ". Comp goes again." << endl;
                }
                else {
                    cout << "You gave your " << count << " " << foundCards.at(0)->getFace() << "'s to the Comp. Comp goes again. " << endl;
                }
            }
            foundCards.clear();

        } while (cardFound != false);
        if (checkForBooks(compHand, compBookCount) == 0) {
            cout << endl << endl << "No new books for Comp this turn." << endl << endl;
            cout << "Player score: " << playerBookCount << endl;
            cout << "Comp score: " << compBookCount << endl << endl;
        }
        else {
            checkForBooks(compHand, compBookCount);
            cout << endl << endl << "Comp got new books." << endl;
            cout << "Player score: " << playerBookCount << endl;
            cout << "Comp score: " << compBookCount << endl << endl;
        }
    }

    if (playerBookCount > compBookCount) {  //once combined book count = 13, check who wins the game

        cout << "You win!!";
    }
    else {

        cout << "You lose...";
    }

    return 0;
}



deque<card*> buildDeck(deque<card*> deck) //build deck, deal hand.
{
  
    

    string hearts = "hearts";
    string diamonds = "diamonds";
    string spades = "spades";
    string clovers = "clubs";
    string two = "2";
    string three = "3";
    string four = "4";
    string five = "5";
    string six = "6";
    string seven = "7";
    string eight = "8";
    string nine = "9";
    string ten = "10";
    string jack = "J";
    string queen = "Q";
    string king = "K";
    string ace = "A";
    vector<string> face;
    face.insert(face.end(), { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace });

    int position = 0;
    for (int i = 0; i < 4; i++)
    {

        if (i == 0) {
            for (int j = 0; j < 13; j++) {
                card* Heart = new card; Heart->setSuit(hearts); deck.push_back(Heart);
            }
        }

        else if (i == 1) {
            for (int j = 0; j < 13; j++) {
                card* Diamond = new card; Diamond->setSuit(diamonds); deck.push_back(Diamond);
            }
        }

        else if (i == 2) {
            for (int j = 0; j < 13; j++) {
                card* Spade = new card; Spade->setSuit(spades); deck.push_back(Spade);
            }
        }

        else {
            for (int j = 0; j < 13; j++) {
                card* Clover = new card; Clover->setSuit(clovers); deck.push_back(Clover);
            }
        }

        for (int k = 0; k < 13; k++)
        {
            deck[position]->setFace(face[k]);
            position++;
        }
    }
   
    srand(unsigned(time(NULL)));
    random_shuffle(deck.begin(), deck.end(), myRand);

    return deck;
}



bool searchHand(string choice, vector<card*>& hand, vector<card*>& foundCard) {
    

    for (int i = 0; i < hand.size(); i++) {
        if (hand.at(i)->getFace() == choice) {
            foundCard.push_back(hand.at(i));
            hand.erase(hand.begin() + i);  // Remove the found card from the hand
            return true;  // Return true after finding one card
        }
    }

    return false;  // Return false if no card was found
}




string compTurn(vector<card*>& hand, string& lastAskedCard) { //dictates comp behavior. if comp hold's 3 of a kind in hand, ask for that card. unless that card was asked
                                                                //for on previous turn, then ask for cards with 2 of a kind. lastly if none of those conditions are met
    std::map<string, int> cardCounts;                           //ask for random card. lastAskedCard prevents computer from making repetitive requests for same card.


    for (int i = 0; i < hand.size(); i++) {
        string face = hand.at(i)->getFace();
        cardCounts[face]++;
    }


    for (int i = 0; i < hand.size(); i++) {
        string face = hand.at(i)->getFace();


        if (cardCounts[face] > 2 && face != lastAskedCard) {
            lastAskedCard = face;
            return face;
        }


        if (cardCounts[face] == 2 && face != lastAskedCard) {
            lastAskedCard = face;
            return face;
        }
    }

    int randomCardValue = rand() % hand.size() + 0;

    while (hand.at(randomCardValue)->getFace() == lastAskedCard)
    {
        int randomCardValue = rand() % hand.size() + 0;
        
    }

    return hand.at(randomCardValue)->getFace();

}


int checkForBooks(vector<card*>& hand, int& bookCount) { //uses same process to check for 4 of a kind in respective hand, removes cards if 4 of a kind is encountered
    std::map<string, int> cardCounts;                   //and increments bookCount.

    int newBookCount = bookCount;

    
    for (int i = 0; i < hand.size(); i++) {
        string face = hand.at(i)->getFace();
        cardCounts[face]++;
    }

    std::map<string, int>::iterator it;

    vector<card*> newHand; 

    for (it = cardCounts.begin(); it != cardCounts.end(); ++it) {
        string face = it->first;
        if (it->second == 4) {
            bookCount++;
            
            hand.erase(
                std::remove_if(hand.begin(), hand.end(),
                    [face](card* c) { return c->getFace() == face; }),
                hand.end()
            );
        }
    }

    newBookCount = bookCount - newBookCount;

    return newBookCount;
}
