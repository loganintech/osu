import sys

stars_number = int(sys.argv[1])
if stars_number % 2 != 1:
    print("That is not an odd number, adding 1.")
    stars_number = stars_number + 1
lines_number = stars_number // 2

for i in range(lines_number + 1):
    print(((stars_number - (i * 2)) // 2) * " ", end="")
    print(("*" * 2 * i) + "*")
