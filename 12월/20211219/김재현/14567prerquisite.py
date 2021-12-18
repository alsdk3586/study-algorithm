import sys

n, m = map(int, sys.stdin.readline().split())

data = []

data = [[] for _ in range(n)] 
res = [0] * n
for _ in range(m):
    a, b = map(int, input().split())
    data[b-1].append(a)

ans = [0] * n
def way(x):
    max = 0
    if len(data[x]) == 0:
        ans[x] = 1
    else:
        for i in range(n):
            if i+1 in data[x]: 
                if max <= ans[i]:
                    max = ans[i] +1
        ans[x] = max

for i in range(n):
    way(i)

print(*ans, sep=' ')