joules_per_gigahash = .1
joules_per_hash = .0000000001
gigahash = 1_000_000_000
joules_per_killowatt_hour = 3_600_000


def cost_of_hash_count(hash_count):
    joules = joules_per_hash * hash_count
    kwh_used = joules / joules_per_killowatt_hour
    return kwh_used * 2


# print(cost_of_hash_count(2 ** 40))
# print(cost_of_hash_count(2 ** 50))
print(cost_of_hash_count(2 ** 120))

# print("{:.2E}".format(joules_per_killowatt_hour / joules_per_hash))
# print("{:.2E}".format(2 ** 40))
# print("{:.2E}".format(2 ** 50))
# print("{:.2E}".format(2 ** 120))

print(cost_of_hash_count(2 ** 120) / (100 * 1000))
