from algorithms import *
from checkers import *

def main():
    degSeqs = [[4,4,4,4,4], 
               [3,3,3,3,3,3], 
               [3,3,3,3,3,3,3,3], 
               [3,3,3,3,3,3,3,3,3], 
               [2,2,2,2,2,2,2,2,2,2],
               [7,6,6,6,5,5,2,1],
               [4,3,3,2,0]
    ]

    for seq in degSeqs:
        print(f"Trying Sequence: {seq}")
        GraphGen(seq)
        print("Try Complete\n")

if __name__ == "__main__":
    main()