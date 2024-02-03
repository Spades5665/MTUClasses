import numpy as np

# Finds an i and j such that the equation 5 * A[i] + 14 * B[j] - 7 = m holds true if an i and j exist
def solve1(A, B, n, m):
    i = 0
    j = n - 1
    while (i < n and j > 0):
        sum = 5 * A[i] + 14 * B[j] - 7
        if (sum == m):
            return True, i, j
        elif (sum > m):
            j -= 1
        elif (sum < m):
            i += 1
    return False, -1, -1

# Random array test
n = 5
m = 20
A = np.random.randint(-100, 100, n)
B = np.random.randint(-100, 100, n)
A.sort()
B.sort()

print("Random Test")
print("A:", A)
print("B:", B)
print("m:", m)
print("")
ans, i, j = solve1(A, B, n, m)

if (ans):
    print("Answer Found:")
    print("i:", i)
    print("j:", j)
else:
    print("No Solution")
print("")

# Set example test
n = 5
A = [-2, -1, 0, 1, 2]
B = [-2, -1, 0, 1, 2]
m = 21

print("Fixed Test")
print("A:", A)
print("B:", B)
print("m:", m)
print("")
ans, i, j = solve1(A, B, n, m)

if (ans):
    print("Answer Found:")
    print("i:", i)
    print("j:", j)
else:
    print("No Solution")
print("")