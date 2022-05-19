import sys
from enum import Enum

##################################
# DESC: Set's up character enums
# PARAM: Takes no parameters
# PRECON: No preconditions
# POSTCON: No postconditions
# RETURNS: Returns nothing
##################################
class Character(Enum):
    X = 1
    O = 0
    E = -1

##################################
# DESC: Gets a players turn
# PARAM: Takes the game board and the character to add
# PRECON: Game must be setup, character must be chosen
# POSTCON: Game board has an extra piece in it
# RETURNS: Returns the game board
##################################
def get_turn(game, player_character):
    done_valid_move = False
    while not done_valid_move:
        try:
            move = input("Please input the place you want to put your piece player " + player_character.name + " (from top left being 0,0 and bottom right 2,2 etc): ")
            x_index = int(move[2])
            y_index = int(move[0])
            if isinstance(y_index, int) and isinstance(x_index, int) and x_index >= 0 and x_index <= 2 and y_index >= 0 and y_index <= 2 and game[x_index][y_index] == Character.E.value:
                game[x_index][y_index] = player_character.value
                return game
            else:
                print("There is already a value or you tried an out of bounds number for this location, please try again.")
        except (IndexError, ValueError):
            print("Not a valid move, please do (x,y) within the bounds of 0 to 2.")

##################################
# DESC: Checks if someone has won horizontally
# PARAM: Takes the game board as a parameter
# PRECON: The game board is created
# POSTCON: Someone wins or the game continues
# RETURNS: Returns whether someone won, and who
##################################
def check_horizontal_win(game):
    if game[0][0] == game[0][1] and game[0][1] == game[0][2] and game[0][2] != Character.E.value:
        return True, game[0][0]
    elif game[1][0] == game[1][1] and game[1][1] == game[1][2] and game[1][2] != Character.E.value:
        return True, game[1][0]
    elif game[2][0] == game[2][1] and game[2][1] == game[2][2] and game[2][2] != Character.E.value:
        return True, game[2][0]
    else:
        return False, Character.E.value

##################################
# DESC: Checks if someone has won vertically
# PARAM: Takes the game board as a parameter
# PRECON: The game board is created
# POSTCON: Someone wins or the game continues
# RETURNS: Returns whether someone won, and who
##################################
def check_vertical_win(game):
    if game[0][0] == game[1][0] and game[1][0] == game[2][0] and game[2][0] != Character.E.value:
        return True, game[0][0]
    elif game[0][1] == game[1][1] and game[1][1] == game[2][1] and game[2][1] != Character.E.value:
        return True, game[0][1]
    elif game[0][2] == game[1][2] and game[1][2] == game[2][2] and game[2][2] != Character.E.value:
        return True, game[0][2]
    else:
        return False, Character.E.value

##################################
# DESC: Checks if someone has won diagonally
# PARAM: Takes the game board as a parameter
# PRECON: The game board is created
# POSTCON: Someone wins or the game continues
# RETURNS: Returns whether someone won, and who
##################################
def check_diagonal_win(game):
    if game[0][0] == game[1][1] and game[1][1] == game[2][2] and game[2][2] != Character.E.value:
        return True, game[0][0]
    if game[0][2] == game[1][1] and game[1][1] == game[2][0] and game[2][0] != Character.E.value:
        return True, game[0][2]
    else:
        return False, Character.E.value

##################################
# DESC: Runs all the check_direction_win params and returns any that are true
# PARAM: Takes the game board as a parameter
# PRECON: The game board is created
# POSTCON: Someone wins or the game continues
# RETURNS: Returns whether someone won, and who
##################################
def get_win_status(game):
    vert = check_vertical_win(game)
    horizontal = check_horizontal_win(game)
    diag = check_diagonal_win(game)
    if diag[0]:
        return diag
    elif horizontal[0]:
        return horizontal
    elif vert[0]:
        return vert
    else:
        return False, Character.E.value

##################################
# DESC: Checks to see if the board is full
# PARAM: Takes the game board as a parameter
# PRECON: The game board is created
# POSTCON: Continues the game if it isn't full
# RETURNS: Returns if it is full or not
##################################
def board_is_full(game):
    board_full = True
    for topind,top in enumerate(game):
        for bottomind,bottom in enumerate(top):
            if bottom == -1:
                board_full = False
    return board_full

##################################
# DESC: Prints the game board
# PARAM: Takes the game board as a parameter
# PRECON: The game board is created
# POSTCON: The board is printed
# RETURNS: Returns nothing
##################################
def print_board(temp_game):
    arr = [["","",""],["","",""],["","",""]]
    for row in range(len(arr)):
        for item in range(len(arr[row])):
            arr[row][item] = Character(temp_game[row][item]).name if Character(temp_game[row][item]).name != "E" else " "
    print("{} | {} | {}".format(arr[0][0], arr[0][1], arr[0][2]))
    print("---------")
    print("{} | {} | {}".format(arr[1][0], arr[1][1], arr[1][2]))
    print("---------")
    print("{} | {} | {}".format(arr[2][0], arr[2][1], arr[2][2]))
    print("\n\n")

##################################
# DESC: Sets up the game
# PARAM: None
# PRECON: None
# POSTCON: Game is made and starting_piece is selected
# RETURNS: game and starting_piece
##################################
def setup():
    game = []
    for index in range(3):
        game.append([Character.E.value, Character.E.value, Character.E.value])
    starting_piece = Character.O if input("Do you want X or O (x/o): ").lower() == "o" else Character.X
    print("You have chosen " + starting_piece.name)
    return game, starting_piece

##################################
# DESC: Gets the next game piece
# PARAM: Takes the game board and starting piece as parameters
# PRECON: Game is created and starting piece is selected
# POSTCON: We know what piece to play on the board
# RETURNS: The character we should put on the board
##################################
def get_next_piece(game, starting_piece):
    x_num = 0
    o_num = 0
    for top in game:
        for character in top:
            if character == Character.O.value:
                o_num += 1
            elif character == Character.X.value:
                x_num += 1
    if x_num == o_num:
        return Character(starting_piece)
    elif x_num > o_num:
        return Character.O
    else:
        return Character.X

##################################
# DESC: Does everything. The main project and all the stuff.
# PARAM: Takes no parameters
# PRECON: Has no preconditions
# POSTCON: Game is over and program exits
# RETURNS: Nothing
##################################
def main():
    continue_game = True
    while continue_game:
        game, starting_piece = setup()

        while not get_win_status(game)[0] and not board_is_full(game):
            game = get_turn(game, get_next_piece(game, starting_piece))
            print_board(game)
        if get_win_status(game)[0]:
            print("Player " + Character(get_win_status(game)[1]).name + " has won!")
        else:
            print("The board is full and nobody has won!")
        continue_game = False if input("Please enter Q to quit, or anything else to continue. [q]: ").lower() == "q" else True

if __name__ == "__main__":
    main()
