#include "ofApp.h"
#include <vector>
#include "Card.hpp"
#include <string>

using namespace std;

ofApp::~ofApp()
{
    for(int i=0; i<cards.size(); i++)
    {
        delete cards[i];
    }
    
   /* for(int j=0; j<cardsToTest.size(); j++)
    {
        delete cardsToTest[j];
    }*/
}


//--------------------------------------------------------------
void ofApp::setup(){
        
    ofBackground(255, 243, 176);
    backgroundCard.load("background.JPG");
    
    //ofSetFrameRate(1);
    numSetCards = 5;
    buffer = 10; // 10px?
    tries = 0;
    waitTime = 3.0;
    
    cardWidth = 80;
    cardHeight = 100;
    
    gameOverColor = ofColor(255, 0, 0);
    triesColor = ofColor(0, 105, 160);
    matchColor = ofColor(255, 85, 0);
    
    triesFont.load("Helvetica", 18);
    gameOverFont.load("Helvetica", 20);
    matchFont.load("Helvetica", 20);
        
    drawMatchString = false;
    
    startMatchTime = 0;
    
    int maxX = ofGetWindowWidth() - cardWidth - buffer;
    int maxY = ofGetWindowHeight() - cardHeight - buffer;
    
    vector<string> fruits{"apple", "apricot", "blueberry", "cherry", "grape", "kiwi", "lemon", "orange", "pear","raspberry", "strawberry", "watermelon"};
    
    // setup cards
    for(int i=0; i < numSetCards; i++)
    {
        int index = ofRandom(fruits.size());
        string fruit = fruits[index];
        auto position = std::find(fruits.begin(), fruits.end(), fruit);
        if (position != fruits.end()) {
            fruits.erase(position);
        }
        //cout << "fruits array: " << string(fruits) << endl;
        cards.push_back(new Card(findFreePosition(), fruit, cardWidth, cardHeight));
        cards.push_back(new Card(findFreePosition(), fruit, cardWidth, cardHeight));
    }

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(checkIfGameOver()) {
        ofSetColor(gameOverColor);
        gameOverFont.drawString("All cards matched!", ofGetWindowWidth() * 0.45, ofGetWindowHeight() * 0.5);
    }

    for(int i=0; i < cards.size(); i++)
    {
        cards[i]->draw();
    }
    
    updateNumTries();
    
    if(drawMatchString) {
        startMatchTime = ofGetElapsedTimeMillis();
        ofSetColor(matchColor);
        matchFont.drawString("Matched " + matchString + "!", ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
        ofSetColor(255);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    mouseX = x;
    mouseY = y;
    
//    // do it at the top of the function in order to show the player the color of the two cards
    if(cardsToTest.size() == 2) {
        // flip them back
        cardsToTest[0]->flip();
        cardsToTest[1]->flip();
        cardsToTest.clear();
    }
    
    for(int i=0; i<cards.size(); i++)
    {
        bool click = cards[i]->checkIfClicked(mouseX, mouseY);
        if(click)
        {
            cardsToTest.push_back(cards[i]);
            cards[i]->flip();
        }
    }
    testIfCardsMatch();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
ofVec2f ofApp::findFreePosition()
{
    ofVec2f free;
    bool overlap = false;
    
    int windowWidth = ofGetWindowWidth();
    int windowHeight = ofGetWindowHeight();
        
    do {
        int x = ofRandom(buffer, windowWidth - cardWidth - buffer);
        int y = ofRandom(windowHeight * 0.07, windowHeight - cardHeight - buffer);
        
        for(int i = 0; i < cards.size(); i++)
        {
            ofVec2f coordinates = cards[i]->getPosition();
            int cardX = coordinates.x;
            int cardY = coordinates.y;
            
            overlap = (x + cardWidth >= cardX) && (x <= cardX + cardWidth) && (y + cardHeight >= cardY) && (y <= cardY + cardHeight);

            if(overlap) {
                break; // move onto the next
            }
        }
        
        free.x = x;
        free.y = y;
        
    } while (overlap);

    return free;
}

//--------------------------------------------------------------
void ofApp::testIfCardsMatch() {
    
    float timeAtStart = ofGetElapsedTimef();
    
    if(cardsToTest.size() == 2) // actually test
    {
        tries++;
        bool match = cardsToTest[0]->checkIfMatch(cardsToTest[1]);
        if(match)
        {
            string fruit = cardsToTest[0]->getFruit();
            // remove both cards from cards array
            cardsToTest[0]->setActive(false);
            cardsToTest[1]->setActive(false);
            
            // script
            matchString = fruit;
            drawMatchString = true;
            cout << "matched " + fruit + "!" << endl;
        }
    };
}

//--------------------------------------------------------------
bool ofApp::checkIfGameOver() {
    
    int numInactive = 0;
    
    for(int i=0; i < cards.size(); i++)
    {
        numInactive = cards[i]->getActive() ? numInactive : numInactive + 1;
    }
    
    return numInactive == cards.size();
}


void ofApp::updateNumTries() {
    
    ofSetColor(triesColor);
    triesFont.drawString("Tries: " + to_string(tries), ofGetWindowWidth() * 0.8, ofGetWindowHeight() * 0.05);
    ofSetColor(255);
}

