# Assignment 5
## Checking for Understanding - Calculator

### Step 1
#### Problem Analysis

* I do understand the problem. I'm making a multi-functional calculator.
* I input decisions and numbers to output conversions or mathamatical operators. 

### Step 2
#### Program Design

* What are the decisions that need to be made?
* How are you going to calculate the binary number for anything above 255?
* Are you going to ask for the starting exponent?
* Are you going to calculate the starting exponent?


> Design:
> 
> Create a method that asks for a number (0, 1, or 2) that corresponds to each mode in the calculator.
> Depending on the number (use an if) do a different method to output something else.
> For 0, ask for a single input number, convert it to binary, and output it back.
> Do this by going up (starting at 2^(0)) to find out where we need to start. If the 2^(n) is larger than the supplied number, use 2^(n-1) as the starting number.
> Then start from 2^(n-1) and do the conversion from assignment 3 and 4. 
> 
> For the scientific mode, get the operator that the user wants and use an if statement to figure out which math operator corrisponds. Then output the stringified result of that math operation.


### Step 4
#### Program Testing

| Input                          | Output               | Handle                           |
|--------------------------------|----------------------|----------------------------------|
| Scientific Mode ; * ; 3; three | Type Exception       | Ask for a number, repeat         |
| Scientific Mode ; * ; 3; 3.0   | Float Exception      | Cast string to float, then int   |
| Binary to Dec ; Three          | Type Exception       | Ask for a number, repeat         |
| Dec to Binary ; Three          | Type Exception       | Ask for a number, repeat         |
| Binary to Dec ; 2 or greater   | No error, bad result | Reject non 0 or 1 inputs, repeat |

