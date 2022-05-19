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

def do_loop(my_turtle, shape_sides):
    my_turtle.pendown()

    for i in range(shape_sides):
        my_turtle.forward(500 / shape_sides)
        print("Location:", my_turtle.pos())
        my_turtle.right(360 / shape_sides)

    my_turtle.penup()

if __name__ == '__main__':
    window, my_turtle = setup()

    my_turtle = turtle_config(my_turtle)
    #do_loop(my_turtle, int(sys.argv[1]))

    # for i in range(50):
    #     do_loop(my_turtle, i + 2)

    do_loop(my_turtle, 3)
    print("Location:", "moved -150x")
    my_turtle.setx(my_turtle.xcor() - 150)
    do_loop(my_turtle, 4)
    print("Location:", "moved -180y")
    my_turtle.sety(my_turtle.ycor() - 180)
    do_loop(my_turtle, 6)
    print("Location:", "moved +200x")
    my_turtle.setx(my_turtle.xcor() + 200)
    do_loop(my_turtle, 8)

    window.mainloop()
