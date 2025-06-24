'''
Use: The function isDegSeq determines if the inputted sequence of numbers is a valid degree sequence for a simple graph
Input: dSeq is 1d array of numbers
Output: On   successful run, outputs 1 
        On unsuccessful run, outputs -1
'''
def isDegSeq(dSeq):
    result = 1
    size = len(dSeq)
    sum = 0
    equal = 0
    for i in range(size):
        if dSeq[i] >= size: 
            print(f"Not a Degree Sequence: degree at index {i} is greater than or equal to the number of vertices.\n{dSeq[i]} >= {size}")
            result = 0
        if dSeq[i] < 0:   
            print(f"Not a Degree Sequence: degree at index {i} is less than 0.\n{dSeq[i]} >= 0")
            result = 0
        if i < size - 1 and dSeq[i] < dSeq[i+1]:
            print(f"Not a Degree Sequence: degree at index {i} is less than degree at index {i+1}.\n{dSeq[i]} < {dSeq[i+1]}")
            result = 0
        if i < size - 1 and dSeq[i] == dSeq[i+1]: equal = 1
        sum += dSeq[i]
        
    if sum % 2 == 1:
        print(f"Not a Degree Sequence: the sum of the degrees must be even.\n{sum} !/ 2")
        result = 0
    if not equal:
        print(f"Not a Degree Sequence: there must be at least one pair of equal degrees.")
        result = 0
    if dSeq[0] == size-1 and dSeq[size-1] == 0:
        print(f"Not a Degree Sequence: a degree of 0 and a degree of n-1 cannot exist together.")
        result = 0
    
    return result