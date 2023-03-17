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

<img src="https://git.arts.ac.uk/storage/user/650/files/e3396a86-ffca-4cd7-8f5a-c6081cafc590" width="45%"> <img src="https://git.arts.ac.uk/storage/user/650/files/cbd03521-9dfc-4df9-84f2-72e7b25b9ffc" width="45%">


### Game 
This is the main screen where the user can play the game! Depending on the difficulty level chosen, a number of cards will appear on the screen at random locations. The user needs to click on a card, one at a time, to match them up. Only two cards can be face up at any time. If the second card matches the first, they're cleared from the screen. Otherwise, they turn back over.

<img src="https://git.arts.ac.uk/storage/user/650/files/79576c43-7199-427f-9a82-595765528b86" width="30%"> <img src="https://git.arts.ac.uk/storage/user/650/files/95e68339-8a38-4f8a-ad64-db6747f331b5" width="30%"> <img src="https://git.arts.ac.uk/storage/user/650/files/a115fed7-6264-4315-9bca-52f58877ddb7" width="30%">


The number of tries is recorded and displayed at the top of the screen. A try counts as every time a user attempts to match a set of cards (so clicking on two cards = 1 try). 

The locations of each card are randomly generated using a helper function **findFreePosition()** which returns an ofVec2f object. This function uses a do...while loop to generate a random set of (x,y) coordinates, and then loops over each existing card to make sure there is no overlap. If there is an overlap with any card, it breaks and goes into the next loop (so tries again). Otherwise, it assumes a free position and returns that set of coordinates. This function is called each time a new card is created. 

The helper function **testIfCardsMatch()** is called every time two cards are clicked on. It checks that the second card matches the first (using the checkIfMatch() function in the Card class), and if so, sets the active property of both cards to false. This ensures that they aren't drawn to the screen in the subsequent frames. Text is also displayed at the top of the screen for 3 seconds to indicate a match was made. 

<img src="https://git.arts.ac.uk/storage/user/650/files/1164ff01-9cd9-497c-a9b5-6a1d4109a0a5" width="45%"> <img src="https://git.arts.ac.uk/storage/user/650/files/0f853a7b-c0af-4b92-aee2-d6f42b99ba8f" width="45%">

### Game Over
The game moves into the 'game over' screen once all the cards are cleared. This screen tells the user the game is over and to press the spacebar if they want to start again. The keyPressed() function waits for the spacebar to be clicked and if so, sets the 'replay' variable to true so that the game goes back to the start screen. 

<img src="https://git.arts.ac.uk/storage/user/650/files/8ea0f8c9-0787-4b0a-8c98-0ca0acedf24e" width="45%">


## Cards


## Future additions

There are several things I would like to add to the game in the future, including:
1. A timed version - the user has to clear all the cards before the time runs out!
2. Sounds and audio - such as background music and sounds when the player matches the card
3. Button functionality - rather than using the keyboard for difficulty/restarting the game 
