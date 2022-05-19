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

def do_loop(fun, num, my_turtle):
    my_turtle.pendown()

    for i in range(5):
        my_turtle.forward(500 / 5)
        print("Location:", my_turtle.pos())
        my_turtle.right(144)

    my_turtle.penup()

def main(my_turtle):

    my_turtle.onclick(do_loop)


if __name__ == '__main__':
    window, my_turtle = setup()

    my_turtle = turtle_config(my_turtle)
    #do_loop(my_turtle, int(sys.argv[1]))

    # for i in range(50):
    #     do_loop(my_turtle, i + 2)

    main(my_turtle)
    window.mainloop()
