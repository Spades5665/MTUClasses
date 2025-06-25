import numpy as np

def expectedInv(A):
    inv = 0
    for i in range(0, len(A) - 1):
        for j in range(i + 1, len(A)):
            if (A[i] > A[j]):
                inv += 1
    return inv

def Merge(A, l, m, r, inv):
    n1 = m - l + 1
    n2 = r - m
    
    L = [0] * (n1)
    R = [0] * (n2)

    for i in range (0, n1):
        L[i] = A[l + i]
    
    for i in range (0, n2):
        R[i] = A[m + i + 1]
    
    i = 0 
    j = 0
    k = l

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1
            inv[0] += len(L) - i
        k += 1
    
    while i < n1:
        A[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        A[k] = R[j]
        j += 1
        k += 1
    
    #print("A:", A)

def MergeSort(A, l, r, inv):
    if (l < r):
        m = (l + r) // 2

        MergeSort(A, l, m, inv)
        MergeSort(A, m + 1, r, inv)
        Merge(A, l, m, r, inv)



inv = [0, 0]
n = 10
A = np.random.randint(-100, 100, n)
inv[1] = expectedInv(A)

print("Random Sort")
print("Unsorted:", A)

MergeSort(A, 0, n - 1, inv)

print("Sorted:", A)
print("Found Inversions:", inv[0])
print("Expected Inversions:", inv[1])
print("")



inv = [0, 0]
n = 7
A = [-1, 0, -5, 1, 5, 10, 13]
inv[1] = expectedInv(A)

print("Set Sort")
print("Unsorted:", A)

MergeSort(A, 0, n - 1, inv)

print("Sorted:", A)
print("Found Inversions:", inv[0])
print("Expected Inversions:", inv[1])
print("")