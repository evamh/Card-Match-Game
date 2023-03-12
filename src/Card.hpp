//
//  Card.hpp
//  cardMatchGame
//
//  Created by Eva Hayek on 08/03/2023.
//

#ifndef Card_hpp
#define Card_hpp

#include <vector>
#include <stdio.h>
#include "ofMain.h"


class Card
{
private:
    int status;
    int width;
    int height;
    ofColor mainColor;
    ofColor backColor;
    ofVec2f cardPosition;
    bool active;
    
public:
    Card(ofVec2f pos, ofColor color, int w, int h);
    ~Card();
    
    // Getters
    int getWidth();
    int getHeight();
    ofVec2f getDimensions();
    ofVec2f getPosition();
    ofColor getMainColor();
    ofColor getBackColor();
    bool getActive();
    
    // Setters
    void setActive(bool value);
    
    void draw();
    void flip();
    bool checkIfClicked(int mouseX, int mouseY);
    bool checkIfMatch(Card* otherCard);
};


#endif /* Card_hpp */
