import sys

stairSize = int(input())
stairNumbers = [0,0]+ [int(input()) for _ in range(stairSize)]

#조건처리 없이 앞에 두개를 붙여놓는다.
stepped = [[0,0],[0,0]] + [[0,0] for _ in range(stairSize)]


for i in range(2,stairSize+2):
    #0은 바로앞 계단을 안밟는 케이스(앞앞계단에서 큰값만 가지고 온다)
    #1은 바로 앞 계단을 밟는 케이스(3연속 불가이므로 0번만 참조)
    stepped[i][0] = stairNumbers[i]+max(stepped[i-2][0],stepped[i-2][1])
    stepped[i][1] = stairNumbers[i]+stepped[i-1][0]

#마지막 계단에서 가장 큰값 케이스를 찾아서 리턴
print(max(stepped[stairSize+1][0],stepped[stairSize+1][1]))