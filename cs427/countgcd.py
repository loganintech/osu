import math


def countgcd(num):
    counter = 0
    for x in range(num):
        n = math.gcd(x, num)
        if n == 1:
            print(x)
            counter += 1
        else:
            print("Nope: ", x, n)
    return counter


print(countgcd(18))
