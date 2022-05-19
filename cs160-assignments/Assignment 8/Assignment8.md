# Stars
## Problem Analysis
* I need to know how the onclick method works
* I need to know what angle to use to turn every time
* I need to know how many loops there are
* I need to know how to tell if something is clicked
* I need to know what params are passed on click
* I need to know how to reset the turtle.

## Design
* Write a method to determine when something is clicked call it loop and take 2 params
* In that method reset and get turtle config, turn 5 times at 144 degrees each time.
* Reset the environment if clicked again.
* Get the window config from a method so it is the right size.
* Run the window's main loop

-

# Text Drawer

## Problem Analysis
* I need to know how to draw each letter
* I need to know how to set heading of the turtle
* I need to know which letter to get for input
* I need to know how to make sure my turtle doesn't write on top of itself
* I need to know how to make the turtle move

## Design

* I am going to create methods for each letter
    * These methods will have heading movement and all information in it
    * It will also make sure the turtle starts at the right Y coord and moves the correct distance down or across
* I need to get an input loop so that I can ask what people want to write.
* I need to see if people want to continue with the program after a loop
* If they do I need to reset the environment

## Testing

| Input | Expected Out       | Actual Out                             |
|-------|--------------------|----------------------------------------|
| xcv   | xcv                | xcv                                    |
| xgg   | G is not supported | G is not supported, G is not supported |
| xvc   | xvc                | xvc                                    |
| vvvxt | vvvxt              | vvvxt                                  |
