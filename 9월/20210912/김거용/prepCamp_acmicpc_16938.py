import sys

count = 0

N, L,R,X = map(int, input().rstrip().split(' '))
A = list(map(int, input().rstrip().split(' ')))

def findTestCandidates(depth,sumOfDifficulty,use, usedCount, minDifficulty, maxDifficulty):
    global count
    depth +=1
    
    if(use==1):
        sumOfDifficulty += A[depth-1]
        minDifficulty = min(A[depth-1], minDifficulty)
        maxDifficulty = max(A[depth-1], maxDifficulty)
        usedCount += 1
        if(sumOfDifficulty>R): return
    
    if(depth==N-1): 
        if(usedCount<2): return
        if(sumOfDifficulty<L): return
        if(maxDifficulty - minDifficulty < X): return
        
        count +=1
        print(sumOfDifficulty)
        return
    findTestCandidates(depth, sumOfDifficulty, 0, usedCount, minDifficulty, maxDifficulty);
    findTestCandidates(depth, sumOfDifficulty, 1, usedCount, minDifficulty, maxDifficulty);

findTestCandidates(-1, 0,0,0,sys.maxsize,-sys.maxsize - 1);
findTestCandidates(-1, 0,1,0,sys.maxsize,-sys.maxsize - 1);
print(count)