real_num = 12.4
whole_num = 250
message = "Sup"

print(real_num)
print(whole_num)
print(message)

real_num = real_num + 10.6
whole_num = whole_num + 19
message = message + " wooh python"

print(real_num)
print(whole_num)
print(message)

print(message + " this is my whole number: " + str(whole_num) + " " + str(real_num) + " that's pretty cool")

real_num = input("Enter a different real number here: ")
print(real_num + message)

real_num = float(input("Enter another number: "))
print(str(real_num) + message)

num = int(input("Enter a number num: "))
print("Your number is: " + str(num))

num = num ** 10
print("Your new number to the 10th exponent: " + str(num))

