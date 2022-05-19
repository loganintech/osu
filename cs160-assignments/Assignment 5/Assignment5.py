# import sys # for testing purposes only

def mode_select(): #Confirmed works, no bug testing yet
	temp_mode = -1
	temp_mode = int(float(input("Please input what mode you'd like. [0] for decimal to binary, [1] for binary to decimal or [2] for scientific (without [ or ]): ")))
	if not temp_mode in range(0,3):
		print("I'm sorry, but that is not a valid mode, please try again.")
	else:
		print("Thank you, you have selected ", end="")
		if temp_mode == 0:
			print("decimal to binary mode.")
		elif temp_mode == 1:
			print("binary to decimal mode.")
		else:
			print("scientific mode.")

	return temp_mode

	# return int(float(sys.argv[1]))

def math_calculation():
	operation_string = input("Please input the math operator you want (+,-,*,/,**,//): ")
	num1 = int(float(input("Please input the first number you want to compute: ")))
	num2 = int(float(input("Please input the second number you want to compute: ")))
	if operation_string == "+":
		print(num1 + num2)
	elif operation_string == "-":
		print(num1 - num2)
	elif operation_string == "*":
		print(num1 * num2)
	elif operation_string == "/":
		print(num1 / num2)
	elif operation_string == "**":
		print(num1 ** num2)
	elif operation_string == "//":
		print(num1 // num2)
	else:
		print("That is not one of the options. Please try again (+,-,*,/,**,//)")

def int_to_binary(num):
	found_size = False
	num_start = -1
	index = 0
	while not found_size:
		if (2 ** index) > num:
			num_start = 2 ** (index - 1)
			found_size = True
		else:
			index = index + 1
	current_number = ""
	for i in range(index):
		current_number = str(int(num % 2)) + current_number
		num = num / 2
	return int(current_number)

def binary_to_int(num):
	build_me = 0
	for i, item in enumerate(str(num)[::-1]): #[::-1] reverses the string because it begins at the beginning, ends at the end, and has a step of -1 :)
		if int(item) == 0:
			continue
		else:
			build_me = build_me + (2 ** i)
	return build_me

if __name__ == "__main__":
	should_continue = True
	while should_continue:
		calc_mode = -1
		while calc_mode == -1:
			calc_mode = mode_select()
		if calc_mode == 0:
			print(int_to_binary(int(float(input("Please input a number to convert to binary: ")))))
			# print(int_to_binary(int(sys.argv[2]))) # for testing purposes only
		elif calc_mode == 1:
			print(binary_to_int(int(float(input("Please input a binary number to convert to a number: ")))))
		elif calc_mode == 2:
			math_calculation()
		else:
			print("An error has occured.")

		cont = input("Do you want to continue? (yes / no): ")
		if (cont == "no") or (cont == "n"):
			should_continue = False
