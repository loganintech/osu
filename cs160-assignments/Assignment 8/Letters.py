import turtle, sys

def setup():
    window = turtle.Screen()
    my_turtle = turtle.Turtle()
    window.bgcolor("orange")
    return window, my_turtle

def reset_turtle():
    my_turtle.reset()
    my_turtle.color("blue")
    my_turtle.pen(fillcolor="green", pencolor="blue", pensize="5")
    my_turtle.speed(8)
    return my_turtle

def do_loop(letters):
    reset_turtle()

    my_turtle.pendown()

    for letter in letters:
        starting_x = my_turtle.xcor()
        print("STARTING: " + str(starting_x))

        #DRAW LETTERS HERE
        if letter.lower() == "x":
            draw_x()
        elif letter.lower() == "v":
            draw_v()
        elif letter.lower() == "t":
            draw_t()
        elif letter.lower() == "y":
            draw_y()
        elif letter.lower() == "u":
            draw_u()
        elif letter.lower() == "n":
            draw_n()
        #END DRAW LETTERS

        ending_x = my_turtle.xcor()
        print("ENDING: " + str(ending_x))
        x_diff = ending_x - starting_x
        print("DIFFERENCE: " + str(x_diff))
        my_turtle.penup()
        if x_diff < (12 * modifier):
            my_turtle.setx(my_turtle.xcor() + ((12 * modifier) - x_diff))
        my_turtle.pendown()

    my_turtle.penup()

def draw_x():
    print("BEGIN X")
    my_turtle.penup()
    my_turtle.sety(0)
    my_turtle.setheading(-45)
    my_turtle.pendown()
    my_turtle.forward(10 * modifier)
    my_turtle.penup()
    my_turtle.sety(0)
    my_turtle.setheading(225)
    my_turtle.pendown()
    my_turtle.forward(10 * modifier)

def draw_v():
    print("BEGIN V")
    my_turtle.penup()
    my_turtle.sety(0)
    my_turtle.setheading(-60)
    my_turtle.pendown()
    my_turtle.forward(9 * modifier)
    my_turtle.setheading(60)
    my_turtle.forward(9 * modifier)


def draw_t():
    print("BEGIN T")
    my_turtle.penup()
    my_turtle.sety(0)
    my_turtle.setheading(0)
    my_turtle.pendown()
    my_turtle.forward(4 * modifier)
    my_turtle.setheading(270)
    my_turtle.forward(7.4 * modifier)
    my_turtle.setheading(90)
    my_turtle.forward(7.4 * modifier)
    my_turtle.setheading(0)
    my_turtle.forward(4 * modifier)

def draw_y():
    print("BEGIN Y")
    my_turtle.penup()
    my_turtle.sety(0)
    my_turtle.setheading(-35)
    my_turtle.pendown()
    my_turtle.forward(5.5 * modifier)
    my_turtle.setheading(270)
    my_turtle.forward(5 * modifier)
    my_turtle.setheading(90)
    my_turtle.forward(5 * modifier)
    my_turtle.setheading(35)
    my_turtle.forward(5.5 * modifier)

def draw_u():
    print("BEGIN U")
    my_turtle.penup()
    my_turtle.sety(0)
    my_turtle.setheading(270)
    my_turtle.pendown()
    my_turtle.forward(4 * modifier)
    for i in range(8):
        my_turtle.left(180 / 8)
        my_turtle.forward((12 * modifier)/ 8)
    my_turtle.forward(2.3 * modifier)

def draw_n():
    print("BEGIN N")
    my_turtle.penup()
    my_turtle.sety(-7.2 * modifier)
    my_turtle.setheading(90)
    my_turtle.pendown()
    my_turtle.forward(8 * modifier)
    my_turtle.setheading(-50)
    my_turtle.forward(10 * modifier)
    my_turtle.setheading(90)
    my_turtle.forward(8 * modifier)


def get_input(in_string="no_input"):
    if in_string != "no_input":
        return in_string

    while True:
        in_string = input("What string do you want to print? [x,v,t,y,u,n] Input: ").lower()
        supported_letters = ["n","u","y","t","v","x"]
        supported = True
        for i in in_string:
            if i not in supported_letters:
                print("You have included a letter [" + i + "] that is not supported by this program. Please use these: sierac")
                supported = False
                continue
        if supported:
            return in_string

if __name__ == "__main__":
    modifier = 5
    window, my_turtle = setup()

    my_turtle = reset_turtle()

    should_continue = True
    while should_continue:
        try:
            do_loop(get_input(sys.argv[1]))
        except IndexError:
            do_loop(get_input())
        should_continue = True if input("Input c to continue or anything else to quit: ") == "c" else False

        if should_continue == False:
            sys.exit()


    window.mainloop()
