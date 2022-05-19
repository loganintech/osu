# Functions and Looping with Integration

## Program Analysis
* I need to know the left hand reiman sum for calculating integrals.
* I need to know the trapezoidal method for calculating integrals.
* I need to know how to calculate the area of a trapezoid.

## Program Design
* Functions
	* Pick the math function (f(x) stuff) with input or sys.argv
		* We just need to know which function is which, returns a number corresponding to the function number
	* Pick the calc function (rectangular vs trapezoid) with input or sys.argv
		* We need to know which is rectangular and which is trapezoidal and returns a number that corresponds to which one we want (or both)
	* Pick how many regions we need to use to calculate each of the types of the sums with sys.argv and input
		* Arbitrarily picked by the user. The greater this number is, the more accurate the estimation. Returns an int.
	* Pick which point we want to use as a starting point with sys.argv or input
		* Where do we want to start on the curve, returns an int
	* Pick the ending point we want with sys.argv or input
		* Where do we want to end on the curve, returns an int
	* Do the actual math calculation based on function number and x value at that point
		* Send it an int, return an int.
	* Ask if we want to keep going
		* Return a boolean
	* Do the rectangular calculation with the previously picked information
	  * Send it the regions, points, and function and get an int back
	* Do the trapezoidal calculation with the previously picked information
		* Send it the regions, points, and function and get an int back

## Test Cases

| Input                                              | Expected Output                 | Actual Output                          |
|----------------------------------------------------|---------------------------------|----------------------------------------|
| Fun: 3, Calc: 0; Regions: 1, Start: 0, End: 1      | 0                               | 0                                      |
| Fun: 3, Calc: 0; Regions: 3, Start: 0, End: 1      | .11111                          | .1111111111111                         |
| Fun: 2, Calc: 2; Regions: 99999, Start: 0, End: 1  | 24.9999999... and 25            | 24.999 and 25.0                        |
| Fun: 1, Calc: 2; Regions: 9999, Start: 0, End: 10  | 233.283333.... and 233.33333... | 233.28332 and 233.333333               |
| Fun: 4, Calc: 2; Regions: 9999, Start: -2, End: 10 | 7174.77 and 7176.00             | 7174.775935199282 and 7176.00005761154 |
