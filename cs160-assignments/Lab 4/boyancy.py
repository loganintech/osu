import sys, math

y = 62.4
try:
	iterations = int(sys.argv[1])
except IndexError:
	iterations = 1

for i in range(iterations):
	weight = int(input("Please input weight: "))
	radius = int(input("Please input radius: "))
	volume = (4/3) * math.pi * radius ** 3
	boyancy = volume * y
	if boyancy >= weight:
		print("Floats")
	elif boyancy < weight:
		print("Sinks")