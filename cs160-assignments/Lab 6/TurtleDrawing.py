import turtle, sys

def setup():
    window = turtle.Screen()
    my_turtle = turtle.Turtle()
    window.bgcolor("orange")
    return window, my_turtle

def turtle_config(my_turtle):
    my_turtle.color("blue")
    my_turtle.pen(fillcolor="green", pencolor="blue", pensize="5")
    my_turtle.speed(8)
    return my_turtle

def do_loop(my_turtle):
    while True:
        my_turtle.reset()
        turtle_config(my_turtle)
        my_turtle.pendown()

        while True:
            try:
                num_input = int(input("How many sides do you want the shape to have. In: "))
                break
            except ValueError:
                print("That is not a valid input. Retrying.")

        if num_input == 3:
            draw_triangle()
        elif num_input == 4:
            draw_square()
        elif num_input == 6:
            draw_hexagon()
        elif num_input == 8:
            draw_octagon()
        elif num_input == -1:
            draw_pentagram()
        else:
            for i in range(num_input):
                my_turtle.forward(500 / num_input)
                print("Location:", my_turtle.pos())
                my_turtle.right(360 / num_input)

        my_turtle.penup()

        should_continue = False if input("Enter 'q' to quit: ") == "q" else True
        if not should_continue:
            sys.exit()


def draw_triangle():
    for i in range(3):
        my_turtle.forward(500 / 3)
        print("Location:", my_turtle.pos())
        my_turtle.right(360 / 3)

def draw_square():
    for i in range(4):
        my_turtle.forward(500 / 4)
        print("Location:", my_turtle.pos())
        my_turtle.right(360 / 4)

def draw_hexagon():
    for i in range(6):
        my_turtle.forward(500 / 6)
        print("Location:", my_turtle.pos())
        my_turtle.right(360 / 6)

def draw_octagon():
    for i in range(8):
        my_turtle.forward(500 / 8)
        print("Location:", my_turtle.pos())
        my_turtle.right(360 / 8)

def draw_pentagram():
    for i in range(5):
        my_turtle.forward(500 / 5)
        print("Location:", my_turtle.pos())
        my_turtle.right(144)

if __name__ == '__main__':
    window, my_turtle = setup()
    my_turtle = turtle_config(my_turtle)
    do_loop(my_turtle)
    window.mainloop()
