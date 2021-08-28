import sys
 
 
#Process Input And Initialize Data
R, C, sharkNum = map(int, input().rstrip().split(' '))
    
sea = [[0 for _ in range(R)] for _ in range(C)]
sharkDelta = [(-1,0), (1,0), (0,1), (0,-1)] #북남동서 세로이동,가로이동
isSharkMoving=False

def sharkMove(r,c,s,d):
    #최초 좌표는 -1 처리 해준다.
    if(False == isSharkMoving):
        r=r-1
        c=c-1
    else:
        while(s>0):
            s -= 1
            if(d>2): #가로이동
                if(c==0):       d=3
                elif(c==C-1):   d=4
                c=c+sharkDelta[d-1][1]
            else: #세로이동
                if(r==0):       d=2
                elif(r==R-1):   d=1
                r=r+sharkDelta[d-1][0]
    return r,c,d

def catchShark(kingsColumn):
    global sea
    sharkSize = sharkIndex = -1
    
    for seaRow in sea[kingsColumn]:
        if(seaRow!=0):
            sharkSize = int(seaRow/100000)
            sharkIndex = int(seaRow%100000)
            break
    return sharkSize, sharkIndex;

sharkList = [list(map(int, input().rstrip().split(' '))) for _ in range(sharkNum)]


kingsColumn = -1;
catchedSharkSum = 0
while(kingsColumn<C-1):
    deadSharkList = []
    sea = [[0 for _ in range(R)] for _ in range(C)]
    for i in range(len(sharkList)):
        r, c, s, d, z = sharkList[i]
        r,c,d =sharkMove(r,c,s,d);
        #이동 좌표 업데이트
        sharkList[i] = [r, c, s, d, z]
        #print(['/'.join([str(item) for item in sharkList[i]])])
        if(sea[c][r]/100000 < z ):
            #좌표에 있던 놈이 죽거나
            if(sea[c][r]!=0):
                #print(sea[c-1][r-1])
                deadSharkList.append(int(sea[c-1][r-1]%100000))
            sea[c][r] = i+z*100000
        #새로 이동한 놈이 죽거나
        else:
            deadSharkList.append(i)
    print('\n\n'.join(['/'.join([f'{item:06}' for item in row])  for row in sea]))    
    #print(deadSharkList)
    kingsColumn += 1
    sharkSize, sharkIndex = catchShark(kingsColumn);
    if(sharkIndex!=-1):
        catchedSharkSum += sharkSize
        deadSharkList.append( sharkIndex )
    
    #print(deadSharkList)
    print([' '.join([str(item) for item in sharkList[sharkIndex]])])
    for index in sorted(deadSharkList, reverse=True):
        del sharkList[index]
    isSharkMoving = True
            
print(catchedSharkSum)