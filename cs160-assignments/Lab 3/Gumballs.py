c_num = int(input("Please input your coupons here (number): "))
candy = c_num / 10
c_num_leftover = c_num % 10
gumballs = c_num_leftover / 3
print("You have " + str(candy) + " candy bars and " + str(gumballs) + " gumballs.")