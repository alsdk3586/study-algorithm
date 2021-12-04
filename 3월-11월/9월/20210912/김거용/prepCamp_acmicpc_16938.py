import sys

count = 0

N, L,R,X = map(int, input().rstrip().split(' '))
A = list(map(int, input().rstrip().split(' ')))

def findTestCandidates(depth,sumOfDifficulty,use, usedCount, minDifficulty, maxDifficulty):
    global count
    depth +=1
    
    #해당 depth(index)의 문제를 사용한다고 하면
    if(use==1):
        #난이도 총합/최소,최대난이도/문제사용 갯수 업데이트
        sumOfDifficulty += A[depth-1]
        minDifficulty = min(A[depth-1], minDifficulty)
        maxDifficulty = max(A[depth-1], maxDifficulty)
        usedCount += 1
        #난이도 총합이 R초과하면 빠른 종료(아래로 내려갈 필요 없음)
        if(sumOfDifficulty>R): return
    
    if(depth==N-1): 
        #마지막까지 왔으면
        #문제수/난이도합 최소조건/난이도격차 조건 만족 검사
        if(usedCount<2): return
        if(sumOfDifficulty<L): return
        if(maxDifficulty - minDifficulty < X): return
        
        #모든 조건을 만족한 케이스 발견
        count +=1
        return
    
    findTestCandidates(depth, sumOfDifficulty, 0, usedCount, minDifficulty, maxDifficulty);
    findTestCandidates(depth, sumOfDifficulty, 1, usedCount, minDifficulty, maxDifficulty);

#DFS로 전체 탐색
findTestCandidates(-1, 0,0,0,sys.maxsize,-sys.maxsize - 1);
findTestCandidates(-1, 0,1,0,sys.maxsize,-sys.maxsize - 1);
print(count)