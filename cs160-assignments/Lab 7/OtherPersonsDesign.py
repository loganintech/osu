

def get_user_input():
    return input("Give me a string please much wow very string: ")

def percent_matching(string1, string2, match):
    if len(string1) >= len(string2):
        percent = match / len(string1)
    else:
        percent = match / len(string2)
    return percent

def num_matching_chars(string1, string2):
    match = 0
    if len(string1) >= len(string2):
        for index,letter in enumerate(string2):
            if letter == string1[index]:
                match += 1
    else:
        for index,letter in enumerate(string1):
            if letter == string2[index]:
                match += 1

    return match

def main():
    string1 = get_user_input()
    string2 = get_user_input()
    match = num_matching_chars(string1, string2)
    percent = percent_matching(string1, string2, match)
    print(str(percent * 100) + "%")

if __name__ == "__main__":
    main()
