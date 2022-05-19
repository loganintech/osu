# costs = [0, 150, 200, 295, 375, 480, 620]
# costs = [1, 3, 10, 12, 8, 13, 6]
costs = [2, 2, 3, 4]

def lowest_cost(costs):


    if len(costs) == 1:
        return costs[0]


    modified_costs = costs[1:]

    min_val =  min([(cost + lowest_cost(modified_costs[idx:])) for idx, cost in enumerate(modified_costs)])

    return min_val


def lecture_lowest(costs):
    complexity = 0
    computed_costs = [0]
    for j in range(1, len(costs) - 1):
        computed_costs.append(1000000000)
        for i in range(0, j):
            complexity += 1
            computed_costs[j] = min(computed_costs[i] + (costs[j] - costs[i]), computed_costs[j])


    return computed_costs, complexity



comp, complexity = lecture_lowest(costs)
print("Lowest cost {}\nComplexity: {}".format(comp, complexity))

def longest_common_subsequence(X, Y, m, n):
    if m == 0 or n == 0: return 0
    elif X[m-1] == Y[n-1]: return 1 + longest_common_subsequence(X, Y, m-1, n-1)
    else: return max(longest_common_subsequence(X, Y, m, n-1), longest_common_subsequence(X, Y, m-1, n))


global maximum
def _lis(arr, n):
    global maximum
    if n == 1: return 1
    # maxEndingHere is the length of LIS ending with arr[n-1]
    maxEndingHere = 1
    # Recursively get all LIS ending with arr[0], arr[1]..arr[n-2]
    # IF arr[n-1] is maller than arr[n-1], and max ending with
    # arr[n-1] needs to be updated, then update it
    for i in xrange(1, n):
        res = _lis(arr, i)
        if arr[i-1] < arr[n-1] and res+1 > maxEndingHere:
            maxEndingHere = res + 1
    # Compare maxEndingHere with overall maximum. And
    # update the overall maximum if needed
    maximum = max(maximum, maxEndingHere)
    return maxEndingHere
def lis(arr):
    # to allow the access of global variable
    global maximum
    # lenght of arr
    n = len(arr)
    # maximum variable holds the result
    maximum = 1
    # The function _lis() stores its result in maximum
    _lis(arr, n)
    return maximum
