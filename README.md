# Card Match Game - match the cards together!


For my final project, I decided to recreate the classic card match game. This is a memory game where the player is presented with an even number of cards face down, and have to flip them over in order to try and pair them together. Only two cards at most can be face up. If the two cards match, they get taken away. If they don't match, they are flipped over again and the user keeps trying. The game is over once all the cards are cleared!

I recreated this game using openFrameworks and gave it a fruit theme. The aim of the game is to match all the fruits together!

## Code

This game is built in openFrameworks and uses the ofApp() class to run the main logic of the game. 

### Card 

The **Card** class was built to store all of the information relating to a specific card. The variables of a Card include position, width, height and fruit. There are also two ofImage variables, fruitImage and backgroundImage, to designate the front and back of the card.

The methods in **Card** include getters, **draw()** which draws the card to the screen, **flip()** which switches between the front and the back of the card, **checkIfClicked(int mouseX, int mouseY)** to check if the mouse clicked the card and **checkIfMatch(Card * otherCard)** to see if a card was matched to another. The game considers a match to be where two cards have the same fruit image and a different position on the screen (otherwise, the same card could be considered a match with itself!). 

### ofApp

## Cards


## Future additions

There are several things I would like to add to the game in the future, including:
1. A timed version - the user has to clear all the cards before the time runs out!
2. Sounds and audio - such as background music and sounds when the player matches the card
3. Button functionality - rather than using the keyboard for difficulty/restarting the game 
