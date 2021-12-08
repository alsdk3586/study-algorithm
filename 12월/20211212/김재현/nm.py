import sys

n, m = map(int, sys.stdin.readline().split())
data = list(map(int, sys.stdin.readline().split())) 
data.sort()

arr = [0]*(m+1)

def check(x):
    if x == m+1:
        for i in range(1, m+1):
            print(arr[i], end=' ')
        print()
    else:
        for i in range(0, n):
            if arr[m] == 0:
                arr[x] = data[i]
                check(x+1)
                arr[x] = 0
check(1)