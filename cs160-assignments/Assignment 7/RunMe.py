# S I E R A C
import sys

def print_s():
    return_string = []
    return_string.append("*****")
    return_string.append("*    ")
    return_string.append("*****")
    return_string.append("    *")
    return_string.append("*****")
    return return_string

def print_i():
    return_string = []
    return_string.append("*****")
    return_string.append("  *  ")
    return_string.append("  *  ")
    return_string.append("  *  ")
    return_string.append("*****")
    return return_string

def print_e():
    return_string = []
    return_string.append("*****")
    return_string.append("*    ")
    return_string.append("*****")
    return_string.append("*    ")
    return_string.append("*****")
    return return_string

def print_r():
    return_string = []
    return_string.append("***  ")
    return_string.append("* *  ")
    return_string.append("***  ")
    return_string.append("*  * ")
    return_string.append("*   *")
    return return_string

def print_a():
    return_string = []
    return_string.append("   *   ")
    return_string.append("  * *  ")
    return_string.append(" ** ** ")
    return_string.append(" ***** ")
    return_string.append("*     *")
    return return_string

def print_c():
    return_string = []
    return_string.append("*****")
    return_string.append("*    ")
    return_string.append("*    ")
    return_string.append("*    ")
    return_string.append("*****")
    return return_string

def get_user_string(in_string):
    while True:
        in_string = input("What string do you want to print? Input: ").lower()
        supported_letters = ["s","i","e","r","a","c"]
        supported = True
        for i in in_string:
            if i not in supported_letters:
                print("You have included a letter [" + i + "] that is not supported by this program. Please use these: sierac")
                supported = False
                continue
        if supported:
            return in_string

def print_letter(input_letter):
    if input_letter == "a":
        return print_a()
    elif input_letter == "s":
        return print_s()
    elif input_letter == "i":
        return print_i()
    elif input_letter == "e":
        return print_e()
    elif input_letter == "r":
        return print_r()
    elif input_letter == "c":
        return print_c()
    else:
        print("Something super duper went wrong.")

if __name__ == "__main__":
    should_exit = False
    while not should_exit:
        try:
            in_string = sys.argv[1]
        except IndexError:
            in_string = get_user_string("")
        for character in in_string:
            for line in print_letter(character.lower()):
                print(line)
        assembled_lines = []
        for character in in_string:
            for index,line in enumerate(print_letter(character.lower())):
                try:
                    assembled_lines[index] = assembled_lines[index] + " " + line
                except IndexError:
                    assembled_lines.append(line)
        for line in assembled_lines:
            print(line)

        should_exit = True if input("Input q to exit or anything else to continue: ") is "q" else False
