import sys, random

def pick_function(arg=-1):
    if arg == -1:
        try:
            arg = int(float(input("Please input what function you want to use (0,1,2,3,4,quit): ")))
            if arg <= 4 and arg >= 0:
                return arg
            else:
                print("That is not a valid entry. Using random function.")
                return random.randrange(0,5)
        except ValueError:
            print("That is not a number. Using random function.")
            return random.randrange(0,5)
    else:
        return arg

def pick_calc_function(arg=-1):
    if arg == -1:
        try:
            arg = int(float(input("Please input rectangular, trapezoidal, or both (0,1,2): ")))
            if arg <= 2 and arg >= 0:
                return arg
            else:
                print("That is not within the range. Using a random calculation type.")
                return random.randrange(0,3)
        except ValueError:
            print("That is not a number. Using a random calculation type.")
            return random.randrange(0,3)
    else:
        return arg

def pick_regions(arg=1):
    if arg == 1:
        try:
            if arg > 0:
                arg = int(float(input("Please input how many regions you would like: ")))
                return arg
            else:
                print("That is a negative number, using a random number between 1 and 1000.")
                return random.randrange(1,1001)
        except ValueError:
            print("That is not a number, using a random number between 1 and 1000.")
            return random.randrange(1,1001)
    else:
        return arg

def pick_start_point(arg=-1):
    if arg == -1:
        try:
            arg = int(float(input("What start point do you want? ")))
            return arg
        except ValueError:
            print("That is not a valid selection, using 0.")
            return 0
    else:
        return arg

def pick_end_point(arg=-1):
    if arg == -1:
        try:
            arg = int(float(input("What end point do you want? ")))
            return arg
        except ValueError:
            print("That is not a valid selection, using 10.")
            return 10
    else:
        return arg

def do_function(function, x_val):
    if function == 0:
        return (5 * (x_val ** 4)) + (3 * (x_val ** 3)) - (10 * x_val) + 2
    elif function == 1:
        return (x_val ** 2) - 10
    elif function == 2:
        return (40 * x_val) + 5
    elif function == 3:
        return x_val ** 3
    elif function == 4:
        return (20 * (x_val ** 2)) + (10 * x_val) - 2
    else:
        raise TypeError("You have not selected a function yet.")

def ask_keep_going(arg=""):
    if arg == "":
        arg = input("Do you want to continue? (y/n) ")
    if arg.lower() == "y":
        return True
    elif arg.lower() == "n":
        return False
    else:
        print("That is not valid input. Quitting.")
        return False

def rectangle(start, end, regions, function):
    single_width = (end - start) / regions
    area = 0
    for i in range(regions):
        area = area + do_function(function, ((i * single_width) + start))
    return area * (single_width)

def trapezoid(start, end, regions, function):
    single_width = (end - start) / regions
    area = 0
    for i in range(regions):
        area = area + ((do_function(function, (i * single_width) + start) + do_function(function, (i * single_width) + start + single_width)) / 2) * single_width
    return area

if __name__ == "__main__":
    keep_going = True

    while keep_going:
        function = -1
        calc_method = -1
        regions = 1
        starting_point = 0
        ending_point = 1

        try:
            function = pick_function(int(sys.argv[1]))
        except IndexError:
            function = pick_function()
        try:
            calc_method = pick_calc_function(int(sys.argv[2]))
        except IndexError:
            calc_method = pick_calc_function()
        try:
            regions = pick_regions(int(sys.argv[3]))
        except IndexError:
            regions = pick_regions()
        try:
            starting_point = pick_start_point(int(sys.argv[4]))
        except IndexError:
            starting_point = pick_start_point()
        try:
            ending_point = pick_end_point(int(sys.argv[5]))
        except IndexError:
            ending_point = pick_end_point()

        print("Function:", function)
        print("Calculator Method:", calc_method)
        print("Regions:", regions)
        print("Starting Point:", starting_point)
        print("Ending Point:", ending_point)

        if calc_method == 0:
            print(rectangle(starting_point, ending_point, regions, function))
        elif calc_method == 1:
            print(trapezoid(starting_point, ending_point, regions, function))
        elif calc_method == 2:
            print(rectangle(starting_point, ending_point, regions, function))
            print(trapezoid(starting_point, ending_point, regions, function))

        try:
            keep_going = ask_keep_going(sys.argv[6])
            sys.argv[6] = ""
        except IndexError:
            keep_going = ask_keep_going()
