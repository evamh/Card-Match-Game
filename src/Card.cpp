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
Card::Card(ofVec2f pos, string f, int w, int h)
{
    cardPosition = pos;
    width = w;
    height = h;
    
    status = 0; // start with back
    active = true;
    
    fruit = f;
    fruitImage.load("fruits/" + fruit + ".JPG");
    backgroundImage.load("background.JPG");
        
}
//--------------------------------------------------------------
Card::~Card()
{}

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
string Card::getFruit() {
    return fruit;
}

//--------------------------------------------------------------
void Card::draw()
{
    //only draw if active
    if(active)
    {
        if(status == 1) {
            fruitImage.draw(cardPosition.x, cardPosition.y, width, height);
        } else {
            backgroundImage.draw(cardPosition.x, cardPosition.y, width, height);
        }
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
    return (otherCard->getFruit() == fruit && otherCard->getPosition() != cardPosition);
}
