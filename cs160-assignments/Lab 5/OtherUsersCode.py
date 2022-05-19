try:
    user_in = int(input("Insert a number:"))
except ValueError:
    print("Not the right kind of input, dingus.")
    user_in = 13
if user_in % 2 == 0: user_in = user_in + 1
for i in range(user_in):
    print((' ' * (user_in - i - 1)) + ('*' * (2 * i + 1)))
