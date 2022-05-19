def birthday(q, N):
    total = 1
    for i in range(1, q):
        total *= 1 - (i / N)
    return 1 - total


print(birthday(50, 512))  # 0.915722525769864
print(birthday(5, 512))  # 0.019398107775487006
print(birthday(23, 365))  # 0.019398107775487006
