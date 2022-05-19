# No if statements
# Convert a number from 0 - 255 to binary
# 0b10001000 <-- 136

import sys

input_number = int(sys.argv[1])
current_number = []
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)

current_number.insert(0,int(input_number % 2))
input_number = input_number / 2
print(current_number, input_number, input_number % 2)
