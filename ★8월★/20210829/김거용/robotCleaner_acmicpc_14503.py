import sys

#맞았습니다!!	124504KB	128ms	PyPy3 / 수정	1929	

#Process Input And Initialize Data
N,M = map(int, input().rstrip().split(' '))
r,c,d = map(int, input().rstrip().split(' '))
roomToClean = [list(map(int, input().rstrip().split(' '))) for _ in range(N)]

currentDirection = d # 북동남서 순으로 0123

robotHalt = False
clearedAreaCount = 0;
frontDelta = [(-1,0), (0,1), (1,0), (0,-1)] #북동남서 세로이동,가로이동

def areaCleaning(currentR, currentC):
    global clearedAreaCount, roomToClean
    clearedAreaCount += 1;
    roomToClean[currentR][currentC]=2   
    return

def canMove(nextR, nextC, wallCheck=False):
    if 0<=nextR<N and 0<=nextC<M:
        if(False == wallCheck and roomToClean[nextR][nextC]==0):
            return True
        elif(wallCheck and roomToClean[nextR][nextC]!=1):
            return True
            
    return False

def powerOn(currentDirection, currentR, currentC):
    rotationCount = 0
    areaCleaning(currentR, currentC)
    
    while True:
        
        currentDirection = (currentDirection+3)%4 #왼쪽으로 돌아라.
        rotationCount += 1
        nextR = currentR + frontDelta[currentDirection][0]
        nextC = currentC + frontDelta[currentDirection][1]
        #print(str(currentR) + " " + str(currentC) + " / " + str(nextR) + " " + str(nextC))
        #if(currentR==8 and currentC==5 and nextR==7 and nextC==5):
            #print('\n'.join(['/'.join([str(item) for item in row])  for row in roomToClean]))
            #print(canMove(nextR, nextC))
            #print(roomToClean[nextR][nextC])
            #print(rotationCount)
        if(rotationCount<=4 and canMove(nextR, nextC)):
            #print()
            #print(str(currentR) + " " + str(currentC) + " / " + str(nextR) + " " + str(nextC))
            #print(roomToClean[nextR][nextC])
            #전진 후 청소
            currentR = nextR
            currentC = nextC
            rotationCount = 0                        
            areaCleaning(currentR, currentC)
        
        if(rotationCount==4):
            #후진 가능 체크
            nextR = currentR - frontDelta[currentDirection][0]
            nextC = currentC - frontDelta[currentDirection][1]
            if(False==canMove(nextR, nextC, True)):
                return
            
            #후진
            currentR = nextR
            currentC = nextC
            rotationCount = 0

powerOn(currentDirection,r,c)

print(clearedAreaCount)



#삽질의 흔적

#DFS?
def doClean(cd, cr, cc):
    global clearedAreaCount, roomToClean, robotHalt
    currentDirection = cd # 북동남서 순으로 0123
    currentR = cr # 북동남서 순으로 0123
    currentC = cc # 북동남서 순으로 0123
    
    clearedAreaCount += 1;
    roomToClean[currentR][currentC]=2

    searchStartDirection = currentDirection;
    clearedAreaCount_temp = clearedAreaCount
    while True:
        
        currentDirection = (currentDirection+3)%4 #왼쪽으로 돌아라.
        nextR = currentR + frontDelta[currentDirection][0]
        nextC = currentC + frontDelta[currentDirection][1]
        if(canMove(nextR, nextC)):
            doClean(currentDirection, nextR, nextC)
        if(robotHalt):
            print(clearedAreaCount)
            return
        if(searchStartDirection==currentDirection):
            break
    
    #후진 가능 체크
    nextR = currentR - frontDelta[currentDirection][0]
    nextC = currentC - frontDelta[currentDirection][1]
    if(False==canMove(nextR, nextC, True)):
        robotHalt = True
    #print('\n'.join(['/'.join([str(item) for item in row])  for row in roomToClean]))
    return
