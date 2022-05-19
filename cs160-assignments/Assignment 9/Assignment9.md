# 2-D Arrays: Tic Tac Toe
## Problem Analysis
* Comments about the problm
	* I need to keep track of the rows and columns.
	* I need to be able to manipulate this data.
	* I need to know how to print this data in a way that is understandable.
	* I need to be able to get user input in a way they can understand.
	* I need to know how to to ask a user if they want to restart the game.
	* I need to know how to check if someone has won the game.
* Description of Knowledge Base
	* I can use 2D arrays
	* I can change what's in them
	* I can print this in lines by array entry
	* I can get the user input with input
	* I can use while
	* I can use for
	* I can use if
	* I can use try
	* I can use input to restart the game
	* I can check the array for a win condition
## Program Design
* I need a get turn method
    * It will get a valid move in the form of x,y coords starting from 0,0 in the top left to 2,2 in the bottom right
    * It will return a modified version of the board with the correct piece in the right spot
* Check Horizontal Method
    * This method checks to see if any of the horizontals have a winning match and returns the character of the winning version
    * It takes just the game board as a parameter
* Check Vertical Win
    * Same as horizontal but checks up and down the columns
* Check Diagonal Win
    * Same as previous but checks the diagonal threes
* Get Win Status
    * Checks the horizontal vertical and diagonal wins for if they are true and returns the correct one of they are true (as in a win was found)
* Board Is Full
    * Takes the game board as a parameter
    * Just checks every space to make sure it isn't empty.
* Print Board
    * Takes the board as a parameter and prints the board in a way that is pretty.
    * It prints the first row with string formats and keeps going with the characters
* Setup
    * Gets a game and sets up the board as empty. Asks for the starting piece and sets it.
* Get Next Piece
    * Checks for the original pieces and returns the character for whatever turn it is depending on what it started on and whats in the board.
* Main
    * Has a loop to continue the game and calls all the highest level functions.
    * Prints when someone has won and asks if you want to continue at the end of the game.

## Program Implementation / Testing

| Input | Expected Out             | Actual Out                |
|-------|--------------------------|---------------------------|
| x01   | x in the far left middle | x in the far left middle  |
| o22   | o in the bottom right    | o in the bottom right     |
| x20   | x in the upper right     | x in the upper right      |
| o02   | o in the bottom left     | o in the bottom left      |
| o11   | o in the middle middle   | o in the middle middle    |
