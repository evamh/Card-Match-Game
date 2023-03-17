# Card Match Game - match the cards together!

For my final project, I recreated the classic card-match game. This is a memory game where the player is presented with an even number of cards face down, and has to flip them over two at a time in order to try and pair them together. If the two cards match, they get cleared. If they don't match, they are flipped over again. The game is over either once all the cards are cleared, or if time runs out! 

I recreated this game using openFrameworks and gave it a fruit theme. The aim of the game is to match all the fruits together!

*Note*: in the directory *cardMatchGame/bin*, the application file "cardMatchGameDebug" was removed as it was too large to upload to Git. 

## Code

This game is built in openFrameworks and uses the ofApp() class and a new Card() class.

### Card 

The **Card** class stores all of the information relating to a specific card. The variables of a Card include the position, width, height, the fruit and whether the card is active. There are also two ofImage variables, fruitImage and backgroundImage, which are the front and back of the card.

The methods in **Card** include getters, **draw()** which draws the card to the screen, **flip()** which switches between the front and the back of the card, **checkIfClicked(int mouseX, int mouseY)** to check if the user clicked on the card and **checkIfMatch(Card otherCard)** to see if a card was matched to another. The game considers a match to be where two cards have the same fruit image and a different position on the screen (otherwise, the same card could be considered a match with itself!). 

### ofApp

The main logic of the game is in ofApp. The code here sets up the variables for the game, including the various text fonts, colours, timers, the screen status, and helper functions. All of the text is drawn to the screen using ofTrueTypeFont objects.

At the start of the game, the function **setupGame()** is called which creates a game instance. This function resets any variables (like the cards array, the number of tries, the start and elapsed time) and initialises new instances of Card based on a random fruit and location which are pushed into a cards vector array. The number of cards, as well as the timer, is instantiated depends on the difficulty level that the user chose. 

The game is composed of three screens:
1. **Start** - provides the instructions for the game and allows the user to choose the difficulty level
2. **Game** - the main game screen where the user can play the game
3. **Game Over** - the screen shown once the user has matched all the cards/ran out of time. By pressing the space bar the user can go back to the Start screen and play again.

A variable 'screen' keeps track of which screen is currently being drawn. 

### Start
This is the first screen the user sees, and it provides instructions on how to begin the game. The user has to choose a difficulty level using the keyboard ('e' for easy, 'm' for medium and 'h' for hard). The difficulty level sets the total number of cards that the user has to match as well as the timer:
- Easy = 5 sets to match in 30s
- Medium = 10 sets to match in 60s
- Hard = 20 sets to match in 1:30

If the user presses a character other than 'e', 'm' or 'h', text appears on the screen to warn that the character can't be recognised and to try again. 

<img src="https://git.arts.ac.uk/storage/user/650/files/e3396a86-ffca-4cd7-8f5a-c6081cafc590" width="45%"> <img src="https://git.arts.ac.uk/storage/user/650/files/cbd03521-9dfc-4df9-84f2-72e7b25b9ffc" width="45%">

The code for the start screen is in the function **startScreen()**.

### Game 
This is the main screen where the user can play the game! Depending on the difficulty level chosen, a number of cards will appear on the screen at random locations. The user needs to click on a card, one at a time, to match them up. Only two cards can be face up at any time. If the second card matches the first, they're cleared from the screen. Otherwise, they are flipped back. 

<img src="https://git.arts.ac.uk/storage/user/650/files/7ece5513-2b89-4488-95f2-a09fcaf07b34" width="30%"> <img src="https://git.arts.ac.uk/storage/user/650/files/e1ede58d-1251-4430-b180-3887b8e33ce6" width="30%"> <img src="https://git.arts.ac.uk/storage/user/650/files/3f4c1ecd-dbd4-422a-ab0d-984e042df688" width="30%">

The number of tries is displayed at the top of the screen. A try counts as every time a user attempts to match a set of cards (so clicking on two cards = 1 try). The amount of time left is also displayed to the left. 

The locations of each card are randomly generated using a helper function **findFreePosition()** which returns an ofVec2f object. This function uses a do...while loop to generate a random set of (x,y) coordinates and check it doesn't overlap with any other cards. If there is an overlap with any card, it breaks and goes into the next loop (tries again with a new set of randomly generated coordinates). Otherwise, it assumes a free position and returns those x, y values in an ofVec2f object. This function is called every time a card is created. 

The helper function **testIfCardsMatch()** is called every time two cards are clicked. It checks that the second card matches the first (using the checkIfMatch() function in the Card class), and if so, sets the active property of both cards to false. This ensures that they aren't drawn to the screen in the subsequent frames. Text is also displayed at the top of the screen for 3 seconds to indicate a match was made. 

<img src="https://git.arts.ac.uk/storage/user/650/files/4ea9a060-79be-425b-98c6-c610cee7f062" width="45%"> <img src="https://git.arts.ac.uk/storage/user/650/files/f518344b-dea7-4a28-bec6-2843917dc665" width="45%">

The function **checkifGameOver()** runs every frame to check if the game is over by checking whether time ran out (in which case win = false) or that all cards are cleared (more technically, that their 'active' variable is set to false, and in which case win = true).

The code for the game screen is in the function **gameScreen()**.

### Game Over
The game moves into the 'gameOver' screen if either condition is met:
1. All the cards are cleared -> win
2. Time ran out -> lose

Depending on the result, the gameOver screen tells the user that they matched all the cards or that time ran out. In both cases, it will inform the user that they can press the spacebar to play again. The keyPressed() function waits for the spacebar to be pressed and if so, sets the 'replay' variable to true so that the game returns to the start screen. Back in the start screen, the **setupGame()** function is called to reset all game-dependent variables (such as the cards, number of tries, timers, etc). 

<img src="https://git.arts.ac.uk/storage/user/650/files/8ea0f8c9-0787-4b0a-8c98-0ca0acedf24e" width="45%"> <img src="https://git.arts.ac.uk/storage/user/650/files/f18e870b-4fd1-4f20-a7ec-1f492cd1b485" width="45%">

The code for the game over screen is in the function **gameOverScreen()**. 

## Cards

I drew the cards using the Adobe Fresco app, and chose to do a fruit theme. Each fruit has a color scheme which influnces how the card is created. A border is drawn in the main color, a background drawn in a lighter shade of that color, and the fruit itself is drawn in the center. In addition, I drew an image for the back of the cards (first image below). I created cards for the following fruits:
- Apple
- Apricot
- Blueberry
- Cherry
- Grape
- Kiwi
- Lemon
- Orange
- Pear
- Raspberry
- Strawberry 
- Watermelon

<img src="https://git.arts.ac.uk/storage/user/650/files/8423d7fc-6586-4045-aeb3-91d373ebae5b" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/a0191b45-59c3-44a0-8581-29a8268425c4" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/4756356f-a984-454b-965c-d3e42c090eaa" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/81bc2be9-1884-40d0-a6f2-7834ec1cf159" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/f763d490-37ba-4d93-a9e9-ca8a29fc2d62" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/b0091b70-741a-4baa-9c95-c67b06197df9" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/b50b6f9a-3779-46d0-a060-d8190c6a769e" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/9c17fedb-3ee1-42be-af95-58542e7bc2b4" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/8cbb08b7-c4f9-4e14-81b9-bb54e168f8bf" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/7a82a8a4-bf19-4996-be72-cda87111585f" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/6cfba2a1-580a-44d1-8ea3-623f89139eba" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/a97b61c0-e6b4-461a-9b53-3b83d1e9897a" width="10%"> <img src="https://git.arts.ac.uk/storage/user/650/files/6acc60bb-4f99-46b4-b943-560a50381528" width="10%">

The cards are drawn in the game using ofImage objects. 

## Future additions

There are several things I would like to add to the game in the future, including:
1. Sounds and audio - such as background music and sounds when the user matches two cards 
2. Button functionality - rather than using the keyboard for user input like choosing the difficulty or restarting the game
3. Improving the fonts and background - to make it more fun
4. Animation - animate the cards disappearing from the screen when the user matches two cards

## Video

https://git.arts.ac.uk/storage/user/650/files/d9959b3e-9571-493b-aa51-a58943fc1273


