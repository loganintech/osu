import math

# Numbers were chosen by smashing random keys
g = 890345234832475893258923475982652834
a = 13
b = 17

# What the eavesdropper knows on left-hand side
key = (g ** (a * b))
ga = (g ** a)
gb = (g ** b)
gagb = (ga + gb)
gatgb = (ga * gb)

print(round(math.log(key, ga)))
print(round(math.log(key, gb)))
