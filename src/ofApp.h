#pragma once

#include "ofMain.h"
#include "Card.hpp"

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
        float waitTime;
    
        ofVec2f findFreePosition();
        bool checkIfGameOver();
        void testIfCardsMatch();
    
    ofTrueTypeFont triesFont;
    void updateNumTries();
    
    ofColor gameOverColor;
    ofColor triesColor;
		
};
