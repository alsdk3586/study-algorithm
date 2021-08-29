import sys
 
 
#Process Input And Initialize Data
R, C, sharkNum = map(int, input().rstrip().split(' '))
    
sea = [[0 for _ in range(R)] for _ in range(C)]
sharkDelta = [(-1,0), (1,0), (0,1), (0,-1)] #북남동서 / 세로이동  가로이동
isSharkMoving=False

def sharkMove(r,c,s,d):
    #이동거리가 남아 있으면 계속
    while(s>0):
        #방향전환이 필요하면
        if(d==4 and c==0):       d=3
        elif(d==3 and c==C-1):   d=4
        
        elif(d==1 and r==0):     d=2
        elif(d==2 and r==R-1):   d=1
        
        if(d>2):    #가로이동
            c=c+sharkDelta[d-1][1]
        else:       #세로이동
            r=r+sharkDelta[d-1][0]
            
        #이동거리 감소
        s -= 1
    #변경된 좌표와 방향 리턴
    return r,c,d

def catchShark(kingsColumn):
    global sea
    #못찾았으면 -1 리턴
    sharkSize = sharkIndex = -1
    
    #왕이 있는 컬럼을 검사해서 상어가 있으면 꺼낸다
    for seaRow in sea[kingsColumn]:
        if(seaRow!=0):
            sharkSize = int(seaRow/100000)
            sharkIndex = int(seaRow%100000)
            break
    return sharkSize, sharkIndex;

#상어목록
sharkList = [list(map(int, input().rstrip().split(' '))) for _ in range(sharkNum)]

kingsColumn = -1;
catchedSharkSum = 0
#낚시왕이 끝까지 가면서 잡는다.
while(kingsColumn<C-1):
    deadSharkList = []
    sea = [[0 for _ in range(R)] for _ in range(C)]
    #상어리스트에서 상어를 맵에 배치한다
    for i in range(len(sharkList)):
        r, c, s, d, z = sharkList[i]
        
        #이동 좌표 업데이트(첫턴 제외하고 이동 후 상태로 배치)
        if(isSharkMoving):
            r,c,d =sharkMove(r,c,s,d);
        else:
            #최초 저장시 한칸씩 땡겨서 0부터 시작하도록한다
            r=r-1
            c=c-1
        sharkList[i] = [r, c, s, d, z]
        
        #print(['/'.join([str(item) for item in sharkList[i]])])
        if(sea[c][r]/100000 >= z ):
            deadSharkList.append(i)     #새로 이동한 놈이 죽거나
        else:
            if(sea[c][r]!=0):           #좌표에 있던 놈이 죽거나
                deadSharkList.append(int(sea[c-1][r-1]%100000))
            sea[c][r] = i+z*100000  #인덱스/크기 모두 10000까지 가능하므로 100000을 곱해서 분리
    #첫턴 이후로는 상어를 이동 후 배치한다
    isSharkMoving = True
    
    #print('\n\n'.join(['/'.join([f'{item:06}' for item in row])  for row in sea]))    
    #print(deadSharkList)
    
    #상어 배치 완료 후 왕이 한칸 이동해서 catch
    kingsColumn += 1
    sharkSize, sharkIndex = catchShark(kingsColumn);
    
    #잡았으면 더하고 죽은 상어 리스트에 추가
    if(sharkIndex != -1):
        catchedSharkSum += sharkSize
        deadSharkList.append( sharkIndex )
    
    #print(deadSharkList)
    #print([' '.join([str(item) for item in sharkList[sharkIndex]])])
    #죽은 상어를 뒤쪽인덱스부터 상어리스트에서 제거한다.
    for index in sorted(deadSharkList, reverse=True):
        del sharkList[index]
            
print(catchedSharkSum)