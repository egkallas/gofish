#ifndef CARD_H
#define CARD_H
#include<string>
#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::string;
using std::vector;

struct card
{
private:
    string suit;
    string face;

public:

    void setSuit(string newSuit)
    {
        suit = newSuit;
    }
    void setFace(string newFace)
    {
        face = newFace;
    }
    string getSuit()
    {
        return suit;
    }
    string getFace()
    {
        return face;
    }

};

struct cardCounter {

    int count;
    string face;

};




#endif
