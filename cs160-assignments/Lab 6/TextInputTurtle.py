import turtle, sys

def setup():
    window = turtle.Screen()
    my_turtle = turtle.Turtle()
    window.bgcolor("orange")
    my_turtle.color("blue")
    return window, my_turtle

def turtle_config(my_turtle):
    my_turtle.pen(fillcolor="green", pencolor="blue", pensize="5")
    my_turtle.speed(8)
    return my_turtle

def do_loop(my_turtle, shape_sides, special_turning_angle=0):
    my_turtle.pendown()

    for i in range(shape_sides):
        my_turtle.forward(500 / shape_sides)
        print("Location:", my_turtle.pos())
        if special_turning_angle == 0:
            my_turtle.right(360 / shape_sides)
        else:
            my_turtle.right(special_turning_angle)

    my_turtle.penup()

def real_main(my_turtle):
    should_run = True
    while should_run:
        my_turtle.reset()
        has_no_input = True
        while has_no_input:
            try:
                turtle_input = int(input("What kind of shape do you want to draw? Input the number of sides: "))
                has_no_input = False
            except ValueError:
                print("That is not an decimal number. Please try again.")
            try:
                special_turning_angle = int(input("Input a special turning angle (optional): "))
            except ValueError:
                special_turning_angle = 0
        do_loop(my_turtle, turtle_input, special_turning_angle)
        should_continue = input("Do you want to continue? (y/n)")
        if should_continue == "n":
            should_run = False
            sys.exit()


if __name__ == '__main__':
    window, my_turtle = setup()

    my_turtle = turtle_config(my_turtle)
    #do_loop(my_turtle, int(sys.argv[1]))

    # for i in range(50):
    #     do_loop(my_turtle, i + 2)

    real_main(my_turtle)

    window.mainloop()
