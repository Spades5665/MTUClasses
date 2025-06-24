from checkers import *

'''
Use: The function runHHAlg runs the Havel-Hakimi Algorithm on a degree sequence of a graph
Input: dSeq is a valid degree sequence in 1d array form
Output: On   successful run, outputs a 2d array holding edge connections. 
        [a, b] represents a vertex at index a in dSeq is connected to a vertex at index b in dSeq
        On unsuccessful run, outputs -1
'''
def runHHAlg(dSeq):
    sum = 0                                             # Holds the sum of connections in dSeq
    amt = 0                                             # Holds the difference between highInd and lowrInd
    conLeft = 0                                         # Holds the number of connections left to make
    fromInd = 0                                         # Index of the current position in dSeq to make connections from
    destInd = 0                                         # Index of the position in dSeq to make connections to 
    lowrInd = 0                                         # Index of the lower end of vertices in dSeq to check for adding connections
    highInd = 0                                         # Index of the higher end of vertices in dSeq to check for adding connections
    rowsInd = 0                                         # Index of next row to update in arr

    for i in range(len(dSeq)): sum += dSeq[i]           # Calculates sum
    arr = [[0] * 2 for _ in range(sum // 2)]            # Sets up 2d array
    
    for fromInd in range(len(dSeq)):                    # Loops through dSeq
        conLeft = dSeq[fromInd]                         # Grabs the degree value from dSeq at index fromInd
        lowrInd = highInd = fromInd + 1                           # Sets starting search index
        while conLeft > 0:                              # Loops until all connections are made for index fromInd
            #highInd = lowrInd + 1                       
            #if nextInd > len(dSeq): return -1

            while dSeq[lowrInd] == dSeq[highInd]: 
                highInd += 1
                if highInd == len(dSeq): break
            
            amt = highInd - lowrInd
            
            if amt > conLeft: lowrInd += amt - conLeft
            for destInd in range(lowrInd, highInd):
                if dSeq[destInd] == 0: 
                    print("Algorithm Failed")
                    return -1
                
                dSeq[destInd] -= 1
                arr[rowsInd][0] = fromInd
                arr[rowsInd][1] = destInd
                rowsInd += 1
                conLeft -= 1
            
            lowrInd += amt

    print(f"Solution Found:")
    for row in arr: print(row)
    return arr

def GraphGen(dSeq):
    if isDegSeq(dSeq): return runHHAlg(dSeq)
    return -1