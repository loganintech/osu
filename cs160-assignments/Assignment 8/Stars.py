import turtle

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

def do_loop(x, y):
    reset_turtle()
    my_turtle.pendown()

    for i in range(5):
        my_turtle.forward(150)

        print("Location:", my_turtle.pos())
        my_turtle.right(144)

    my_turtle.penup()


if __name__ == "__main__":
    window, my_turtle = setup()

    my_turtle = reset_turtle()

    my_turtle.onclick(do_loop)
    window.mainloop()
