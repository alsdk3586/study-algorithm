N = int(input())

matrix = [[0]*N for _ in range(N)]

answer = 0
def go(n):
    if n == N:
        return 1
    ret = 0
    for i in range(N):
        queens[n] = i
        for x,y in enumerate(queens[:n]):
            if abs(n-x) == abs(i-y) or y == i:
                break
        else:
            ret += go(n+1)

    return ret

queens = [None] * (N)
print(go(0))
