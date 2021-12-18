import sys
import math

n = int(sys.stdin.readline().rstrip())

data = list(map(int, sys.stdin.readline().split()))

arr =  list(map(int, sys.stdin.readline().split()))

ans = []

MM = []

# 계산 함수
def cal2(data, ans):
    AA = data[0]
    for i in range(len(ans)):
        if ans[i] == 0:
            AA = AA + data[i+1]
        elif ans[i] == 1:
            AA = AA - data[i+1]
        elif ans[i] == 2:
            AA = AA * data[i+1]
        else:
            AA = int(AA/data[i+1])
    return AA
        


# 백트레킹
def cal(x):
    if sum(arr) == 0:
        res = cal2(data, ans)
        MM.append(res)
    else:
        for i in range(4):
            if arr[i] != 0:
                arr[i] -= 1
                ans.append(i)
                cal(x+1)
                arr[i] += 1
                ans.pop()
                
cal(0)

print(max(MM))
print(min(MM))