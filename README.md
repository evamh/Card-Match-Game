# Card Match Game - match the cards together!


For my final project, I decided to recreate the classic card match game. This is a memory game where the player is presented with an even number of cards face down, and have to flip them over in order to try and pair them together. Only two cards at most can be face up. If the two cards match, they get taken away. If they don't match, they are flipped over again and the user keeps trying. The game is over once all the cards are cleared!

I recreated this game using openFrameworks and gave it a fruit theme. The aim of the game is to match all the fruits together!

## Code

This game is built in openFrameworks and uses the ofApp() class to run the main logic of the game. 

### Card 

The **Card** class was built to store all of the information relating to a specific card. The variables of a Card include position, width, height and fruit. There are also two ofImage variables, fruitImage and backgroundImage, to designate the front and back of the card.

The methods in **Card** include getters, **draw()** which draws the card to the screen, **flip()** which switches between the front and the back of the card, **checkIfClicked(int mouseX, int mouseY)** to check if the mouse clicked the card and **checkIfMatch(Card * otherCard)** to see if a card was matched to another. The game considers a match to be where two cards have the same fruit image and a different position on the screen (otherwise, the same card could be considered a match with itself!). 

### ofApp

The main logic of the game is in ofApp. This sets up the variables for the game, including the various text fonts, the font colours and background colour, boolean values that are used to decide at which stage the game is at, and helper functions. All of the text is drawn to the screen using ofTrueTypeFont objects.

The game is composed of three screens:
1. **Start** - provides the instructions for the game and allows the user to choose the difficulty level
2. **Game** - the main game screen where the user can play the game
3. **Game Over** - the screen shown once the user has matched all the cards. By pressing the space bar the user can go back to the Start screen and play again.


### Start
This is the first screen the user sees, and it provides instructions on how to begin the game. The user has to choose a difficulty level using the keyboard ('e' for easy, 'm' for medium and 'h' for hard). The difficulty level sets the total number of cards that the user has to match together:
- 5 sets for difficulty = easy
- 10 sets for difficulty = medium
- 20 sets for difficulty = hard

If the user presses a character other than 'e', 'm' or 'h', text appears on the screen to warn that the character can't be recognised and to try again. 

### Game 
This is the main screen where the user can play the game! Depending on the difficulty level chosen, a number of cards will appear on the screen at random locations. The user needs to click on a card, one at a time, to match them up. Only two cards can be face up at any time. If the second card matches the first, they're cleared from the screen. Otherwise, they turn back over.

The number of tries is recorded and displayed at the top of the screen. A try counts as every time a user attempts to match a set of cards (so clicking on two cards = 1 try). 

The locations of each card are randomly generated using a helper function **findFreePosition()** which returns an ofVec2f object. This function uses a do...while loop to generate a random set of (x,y) coordinates, and then loops over each existing card to make sure there is no overlap. If there is an overlap with any card, it breaks and goes into the next loop (so tries again). Otherwise, it assumes a free position and returns that set of coordinates. This function is called each time a new card is created. 

The helper function **testIfCardsMatch()** is called every time two cards are clicked on. It checks that the second card matches the first (using the checkIfMatch() function in the Card class), and if so, sets the active property of both cards to false. This ensures that they aren't drawn to the screen in the subsequent frames. Text is also displayed at the top of the screen for 3 seconds to indicate a match was made. 


### Game Over

## Cards


## Future additions

There are several things I would like to add to the game in the future, including:
1. A timed version - the user has to clear all the cards before the time runs out!
2. Sounds and audio - such as background music and sounds when the player matches the card
3. Button functionality - rather than using the keyboard for difficulty/restarting the game 
