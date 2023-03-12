//
//  Card.cpp
//  cardMatchGame
//
//  Created by Eva Hayek on 08/03/2023.
//

#include "Card.hpp"
#include "ofMain.h"
#include <vector>

using namespace std;

//--------------------------------------------------------------
Card::Card(ofVec2f pos, ofColor color, int w, int h)
{
    backColor = ofColor(255, 0, 0);
    cardPosition = pos;
    width = w;
    height = h;
    
    status = 0; // start with back
    active = true;
    
    mainColor = color;
        
}
//--------------------------------------------------------------
Card::~Card()
{
    
}

// Getters
//--------------------------------------------------------------
int Card::getWidth() {
    return width;
}

//--------------------------------------------------------------
int Card::getHeight() {
    return height;
}

//--------------------------------------------------------------
ofVec2f Card::getDimensions() {
    return ofVec2f(width, height);
}

//--------------------------------------------------------------
ofColor Card::getMainColor() {
    return mainColor;
}

//--------------------------------------------------------------
ofColor Card::getBackColor() {
    return backColor;
}

//--------------------------------------------------------------
ofVec2f Card::getPosition() {
    return cardPosition;
}

//--------------------------------------------------------------
bool Card::getActive() {
    return active;
}

//--------------------------------------------------------------
void Card::setActive(bool value) {
    active = value;
}

//--------------------------------------------------------------
void Card::draw()
{
    //only draw if active
    if(active)
    {
        ofColor colorToDraw = (status == 1) ? mainColor : backColor;
        ofSetColor(colorToDraw);
        ofDrawRectangle(cardPosition, width, height);
    }
}

//--------------------------------------------------------------
// flip()
void Card::flip()
{
    status = !status;
}

//--------------------------------------------------------------
bool Card::checkIfClicked(int mouseX, int mouseY)
{
    float x = cardPosition.x;
    float y = cardPosition.y;
    bool click = (mouseX >= x) && (mouseX <= x + width) && (mouseY >= y) && (mouseY <= y + height);
    
    return click && active;
}

//--------------------------------------------------------------
bool Card::checkIfMatch(Card* otherCard) {
    return otherCard->getMainColor() == mainColor;
}
