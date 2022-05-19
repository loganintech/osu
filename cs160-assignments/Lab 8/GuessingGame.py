import random

def get_guesses(guesses, guess_num):
    if not guess_num > 0:
        return -1

    got_guess = False
    while not got_guess:

        try:
            guess = int(input("Please input a number from 1 to 20 here as a guess: "))
        except ValueError:
            print("That is not a valid entry, please try again.")
            continue

        if check_guesses(guess, guesses):
            print("You have already guessed that.")
            continue
        else:
            got_guess = True


    guess_num -= 1
    guesses.append(guess)
    return guess_num

def check_guesses(guess, guesses):
    return guess in guesses

def main():

    should_play = True

    while should_play:

        guess_num = 5
        guesses = []
        random.seed()
        win_num = random.randint(1, 20)

        print("I have made a random number.")

        has_guessed_correctly = False
        while not has_guessed_correctly:
            guess_num = get_guesses(guesses, guess_num)
            if guess_num == -1:
                print("You are out of turns.")
                print("The win number was " + str(win_num))
                break
            elif win_num in guesses:
                print("You have won! The win number was " + str(win_num))
                break

        should_play = False if input("Enter q if you want to quit, anything else to play again: ") == "q" else True


if __name__ == "__main__":
    main()
