//
//  CardSet.hpp
//  cardMatchGame
//
//  Created by Eva Hayek on 08/03/2023.
//

#ifndef CardSet_hpp
#define CardSet_hpp

#include <stdio.h>
#include "Card.hpp"

class CardSet {
private:
    Card* card1;
    Card* card2;
    string cardFruit;
    
public:
    CardSet(string fruit, ofVec2f pos1, ofVec2f pos2, int w, int h);
    ~CardSet();
    Card* getCard1();
    Card* getCard2();
    bool checkIfMatch(Card* testCard1, Card* testCard2);
    
};

#endif /* CardSet_hpp */
