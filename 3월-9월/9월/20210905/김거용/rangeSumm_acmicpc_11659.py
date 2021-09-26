import sys

numSize, numOfSum = map(int, input().rstrip().split(' '))
numList = [0] + list(map(int, input().rstrip().split(' ')))
rangeList = [list(map(int, input().rstrip().split(' '))) for _ in range(numOfSum)]

totalSum = 0

for i in range(numSize):
    numList[i+1] += numList[i]

for start,end in rangeList:
    print(numList[end] - numList[start-1])

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