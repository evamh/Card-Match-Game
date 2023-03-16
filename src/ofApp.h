#pragma once

#include "ofMain.h"
#include "Card.hpp"
#include <vector>
#include "ofxGui.h"

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void setupGame();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        ~ofApp();
        int numSetCards;
        int cardWidth;
        int cardHeight;
        vector<Card *> cards;
        vector<Card *> cardsToTest;
        
        int mouseX;
        int mouseY;
        
        int buffer; // for buffer between cards
    
        int tries;
    
        ofVec2f findFreePosition();
        bool checkIfGameOver();
        void testIfCardsMatch();
    
    // screens in the game 
    void startScreen();
    void gameScreen();
    void gameOverScreen();
    
    //bool startGame;
    string screen;
    bool difficultyChosen;
    bool replay;
    bool addWrongChoiceText;
    
    ofTrueTypeFont triesFont;
    ofTrueTypeFont matchFont;
    ofTrueTypeFont gameOverFont;
    ofTrueTypeFont instructionsFont;
    ofTrueTypeFont wrongChoiceFont;
    
    ofColor gameOverColor;
    ofColor matchColor;
    ofColor triesColor;
    ofColor instructionsColor;
    
    string matchString;
    bool drawMatchString;
    
    void updateNumTries();

    int startMatchTime;
    
    ofImage backgroundCard;
    string getRandomFruit(vector<string> &fruits);
    		
};
