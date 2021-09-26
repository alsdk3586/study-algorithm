import sys


#Process Input And Initialize Data
N,M,K = map(int, input().rstrip().split(' '))
fertilizerPerYear = [list(map(int, input().rstrip().split(' '))) for _ in range(N)]
fertilityOnTheLand = [[5 for _ in range(N)] for j in range(N)]

treeOnTheLand = [[[] for _ in range(N)] for j in range(N)]
deadtreeOnTheLand = [[[] for _ in range(N)] for j in range(N)]

adjacentCoordList = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

for _ in range(M):
    X,Y,treeAge = map(int, input().rstrip().split(' '))
    treeOnTheLand[X-1][Y-1].append(treeAge)


for i in range(N): 
    for j in range(N):
        treeOnTheLand[i][j].sort()

def spring():
    for i in range(N): 
        for j in range(N):
            deadTrees = []
            liveTrees = treeOnTheLand[i][j]
            fertility = fertilityOnTheLand[i][j]
                        
            for treeAge in list(liveTrees):
                liveTrees.remove(treeAge)
                if(fertility>=treeAge):
                    fertility -= treeAge
                    liveTrees.append(treeAge+1)
                else:
                    deadTrees.append(treeAge)
            
            treeOnTheLand[i][j] = liveTrees;
            deadtreeOnTheLand[i][j] = deadTrees;
            fertilityOnTheLand[i][j] = fertility;

def summer():
    for i in range(N): 
        for j in range(N):
            deadTrees = deadtreeOnTheLand[i][j]
            fertilityOnTheLand[i][j] += sum([item // 2 for item in deadTrees])
            
def fruiting(coord, i, j, seeds):
    X = i+coord[0]
    Y = j+coord[1]
    if 0<=X<N and 0<=Y<N:
        treeOnTheLand[X][Y] = seeds + treeOnTheLand[X][Y]
        
def autumn():
    for i in range(N): 
        for j in range(N):
            fruits = len( [x for x in treeOnTheLand[i][j] if x%5==0] )  
            if fruits>0:
                for coord in adjacentCoordList:
                    fruiting(coord, i, j, [1 for _ in range(fruits)])

def winter():
    for i in range(N): 
        for j in range(N):
            fertilityOnTheLand[i][j] += fertilizerPerYear[i][j]


def countTrees():
    treeCount=0
    for i in range(N): 
        for j in range(N):
            treeCount+=len(treeOnTheLand[i][j])
    return treeCount

#print('\n'.join(['/'.join([str(item) for item in row])  for row in treeOnTheLand]))

for _ in range(K):
    #봄 - Eat or Die
    spring()

    #여름 - Death And Decay
    summer()
    
    #가을 - 교수님..아니 5N년차 나무의 C뿌리기
    autumn();
    
    #겨울 - Fertilizing
    winter()
        
treeCount = countTrees()
print(treeCount);
#print('\n'.join(['/'.join([str(item) for item in row])  for row in treeOnTheLand]))
#print('\n'.join(['/'.join([str(item) for item in row])  for row in fertilityOnTheLand]))

