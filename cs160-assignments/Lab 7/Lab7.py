import sys

###########################################################################
# Function Name: Get User Input
# Parameters: user_in
# Pre-Conditions: Must use input()
# Post-Conditions: We have a user input
# Return Values: The user strings
# #########################################################################
def get_user_input(user_in="no_input"):
    if user_in != "no_input":
        return user_in

    return [input("Please input the first string you want to check: "),\
    input("Please input the second string: ")]


###########################################################################
# Function Name: Percent Matching
# Parameters: The Two Strings to find Percent
# Pre-Conditions: Must have the user input
# Post-Conditions: Calculated a percentage similarity of the strings
# Return Values: % of matching string
# #########################################################################
def percent_matching(str1, str2):
    if len(str2) > len(str1):
        str1, str2 = str2, str1
    # str1 should always be the longest one now
    return num_matching_chars(str1, str2) / len(str1)


###########################################################################
# Function Name: Number of Matching Characters
# Parameters: Two strings
# Pre-Conditions: Must have the two strings
# Post-Conditions: A number of matching characters
# Return Values: The number of matching characters
# #########################################################################
def num_matching_chars(long_string, short_string):
    matching_num = 0
    for i,let in enumerate(short_string):
        if short_string[i] == long_string[i]:
            matching_num += 1
    return matching_num


###########################################################################
# Function Name: Main
# Parameters: None
# Pre-Conditions: None
# Post-Conditions: We have the percent matching
# Return Values: Prints matching
# #########################################################################
def main():
    try:
        user_in = get_user_input(sys.argv[1])
    except IndexError:
        user_in = get_user_input()

    print(str(percent_matching(user_in[0], user_in[1]) * 100) + "%")


if __name__ == "__main__":
    main()
