import sys

tmp = list(map(str, sys.stdin.readline().split("\"")))
n = len(tmp)//4
data = [[0,0]] * n

for i in range(n):
    data[i] = [tmp[4*i+1], tmp[4*i+3]]

data.sort()

m = len(data)


def sum(arr):
    sum = 0
    for el in arr:
        sum += el
    return sum
#경로
ans = ['ICN'] + [0] * (m)
# 사용한 티켓
t = [0] * m
end =False
def trable(x):
    global end
    if ans[m-1] != 0:
        ans[m] = data[x][1]
        end = True
    if t[x]:
        return
    else:
        for i in range(m):
            if data[x][1] == data[i][0]:
                t[x] = 1 
                ans[sum(t)] = data[x][1]
                trable(i)
                if(end):
                    return
                t[x] = 0



for i in range(m):
    if data[i][0] == 'ICN':
        trable(i)

print(ans)