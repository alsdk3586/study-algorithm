import sys

n=int(sys.stdin.readline().rstrip())
data = []
for _ in range(n):
    data.append(list(map(int, input().split())))

# 경로
arr = [1] + [0] * (n-1)

ans = set()
#재귀함수 
def trabl(x):
    if not 0 in arr:
        arr[0] = data[x][0]
        sum = 0
        for el in arr:
            sum += el
        ans.add(sum)
    for i in range(1, n):
        if i == x :
            continue
        else:
            if data[x][i] == 0 or arr[i]:
                continue
            else:
                arr[i] = data[x][i]
                trabl(i)
                arr[i] = 0
trabl(0)
smallest = 0
for el in ans:
   if el < smallest or smallest == 0:
       smallest = el
print(smallest)
