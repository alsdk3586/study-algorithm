import sys

stairSize = int(input())
stairNumbers = [0,0]+ [int(input()) for _ in range(stairSize)]

stepped = [[0,0],[0,0]] + [[0,0] for _ in range(stairSize)]

for i in range(2,stairSize+2):
    stepped[i][0] = stairNumbers[i]+max(stepped[i-2][0],stepped[i-2][1])
    stepped[i][1] = stairNumbers[i]+stepped[i-1][0]

print(max(stepped[stairSize+1][0],stepped[stairSize+1][1]))
################################################################

# #Process Input And Initialize Data
# numSize, numOfSum = map(int, input().rstrip().split(' '))
# numList = list(map(int, input().rstrip().split(' ')))
# rangeList = [list(map(int, input().rstrip().split(' '))) for _ in range(numOfSum)]

# sumASC = [0]
# totalSum = 0

# for i in range(numSize):
#     totalSum += numList[i]
#     sumASC.append( totalSum ) #(numList[i] + sumASC[i-1] )
#     #sumDESC.append( numList[numSize-i-1] + sumDESC[i] )


# for start,end in rangeList:
#     print(sumASC[end] - sumASC[start-1])  #start FROM 1

################################################################
# #왜 시간 초과?ㅠㅠ
# #Process Input And Initialize Data
# numSize, numOfSum = map(int, input().rstrip().split(' '))
# numList = [0] + list(map(int, input().rstrip().split(' ')))

# totalSum = 0

# for i in range(numSize):
#     numList[i+1] += numList[i]

# for i in range(numOfSum):
#     start,end = map(int, input().split(' '))
#     print(numList[end] - numList[start-1])  #start FROM 1