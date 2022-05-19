# No if statements
# Convert a number from 0 - 255 to binary
# 0b10001000 <-- 136

import sys

input_number = int(float(sys.argv[1]))

if not (input_number >= 0 and input_number < 256):
	print("Your number is not within the range of 0 to 255 inclusive!")
	sys.exit()

current_number = ""

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

current_number = str(int(input_number % 2)) + current_number
input_number = input_number / 2

print(current_number)