//
//  CardSet.cpp
//  cardMatchGame
//
//  Created by Eva Hayek on 08/03/2023.
//

#include "CardSet.hpp"
#include "Card.hpp"

//--------------------------------------------------------------
CardSet::CardSet(string fruit, ofVec2f pos1, ofVec2f pos2, int w, int h)
{
    cardFruit = fruit;
    card1 = new Card(pos1, fruit, w, h);
    card2 = new Card(pos2, fruit, w, h);
};

//--------------------------------------------------------------
CardSet::~CardSet()
{
}

Card* CardSet::getCard1() {
    return card1;
}

Card* CardSet::getCard2() {
    return card2;
}

bool CardSet::checkIfMatch(Card* testCard1, Card* testCard2) {
    return (testCard1 == card1 && testCard2 == card2) || (testCard2 == card1 && testCard1 == card2);
}
