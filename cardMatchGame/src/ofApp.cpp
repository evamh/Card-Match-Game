#include "ofApp.h"
#include <vector>
#include "Card.hpp"
#include <string>
#include "ofxGui.h"

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
    
    // Setup variables that are constant throughout the game
    ofBackground(255, 243, 176);
    backgroundCard.load("background.JPG");

    buffer = 10; // 10px?
    cardWidth = 80;
    cardHeight = 100;
    
    triesColor = ofColor(0, 105, 160);
    matchColor = ofColor(255, 85, 0);
    instructionsColor = ofColor(245, 16, 62);
    
    string font = "Arial";
    triesFont.load(font, 18);
    gameOverFont.load(font, 16);
    matchFont.load(font, 16);
    instructionsFont.load(font, 16);
    wrongChoiceFont.load(font, 14);
    
    // start with start screen
    screen = "start";
    difficultyChosen = false;
    replay = false;
    addWrongChoiceText = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Logic to switch between screens
    
    // Start screen and user chose difficulty level -> start game!
    if(screen == "start" && difficultyChosen) {
        setupGame();
        screen = "game";
        difficultyChosen = false;
        addWrongChoiceText = false;
    };
    
    // If game is finished, switch to game over screen
    if(screen == "game" && checkIfGameOver()) {
        screen = "gameOver";
    };
    
    // If gameOver and user chose to replay, go back to start screen
    if(screen == "gameOver" && replay) {
        screen = "start";
        replay = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // instructions/start screen
    if(screen == "start") {
        startScreen();
    };
    
    // actual game
    if(screen == "game") {
        gameScreen();
    };

    // game over
    if(screen == "gameOver") {
        gameOverScreen();
    };
}

//--------------------------------------------------------------
void ofApp::setupGame() {

    cards.clear();
    tries = 0;
    drawMatchString = false;
    startMatchTime = 0;

    vector<string> fruits{"apple", "apricot", "blueberry", "cherry", "grape", "kiwi", "lemon", "orange", "pear","raspberry", "strawberry", "watermelon"};
    
    // setup cards
    for(int i=0; i < numSetCards; i++)
    {
        int index = ofRandom(fruits.size());
        string fruit = fruits[index];

        cards.push_back(new Card(findFreePosition(), fruit, cardWidth, cardHeight));
        cards.push_back(new Card(findFreePosition(), fruit, cardWidth, cardHeight));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(screen == "start") {
        switch(key) {
        case 'e':
            numSetCards = 5;
            difficultyChosen = true;
            break;
        case 'm':
            numSetCards = 10;
            difficultyChosen = true;
            break;
        case 'h':
            numSetCards = 20;
            difficultyChosen = true;
            break;
        default:
            addWrongChoiceText = true;
            cout << "wrong choice!" << endl;
        };
        
        //difficultyChosen = true;
    } else if(screen == "gameOver") {
        if(key == ' ') {
            replay = true;
        }
    }
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
            startMatchTime = ofGetElapsedTimeMillis();
            matchString = fruit;
            drawMatchString = true;
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

//--------------------------------------------------------------
void ofApp::updateNumTries() {
    
    ofSetColor(triesColor);
    triesFont.drawString("Tries: " + to_string(tries), ofGetWindowWidth() * 0.8, ofGetWindowHeight() * 0.05);
    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::startScreen() {
    ofSetColor(instructionsColor);
    instructionsFont.drawString("Welcome to the card match game!\nMatch all the cards together to win!\n\n Please choose your difficulty level:\n\n 'e' (easy), 'm' (medium), 'h' (hard)", ofGetWindowWidth() * 0.3, ofGetWindowHeight() * 0.4);
    
    if(addWrongChoiceText) {
        ofSetColor(instructionsColor);
        wrongChoiceFont.drawString("Whoops, can't recognize that character! Please try again!", ofGetWindowWidth() * 0.25, ofGetWindowHeight() * 0.7);
    }
}

//--------------------------------------------------------------
void ofApp::gameScreen() {

    for(int i=0; i < cards.size(); i++)
    {
        cards[i]->draw();
    }
    
    updateNumTries();
    
    // when there's a match, display a message with the fruit for 3 seconds
    if(drawMatchString) {
        if(ofGetElapsedTimeMillis() - startMatchTime < 10000) {
            ofSetColor(matchColor);
            matchFont.drawString("Matched " + matchString + "!", ofGetWindowWidth() * 0.3, ofGetWindowHeight() * 0.05);
            ofSetColor(255);
        } else {
            drawMatchString = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::gameOverScreen() {
    drawMatchString = false;
    ofSetColor(instructionsColor);
    gameOverFont.drawString("All cards matched!\nWould you like to start again? Press the space bar if so!", ofGetWindowWidth() * 0.2, ofGetWindowHeight() * 0.4);
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
