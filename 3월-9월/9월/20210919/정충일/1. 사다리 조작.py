import sys

n,m,h = map(int, input().split())

if m == 0:
    print(0)
    exit()

bridge = [[False] * n for _ in range(h)]

for _ in range(m):
    a, b = map(int, input().split())
    bridge[a-1][b-1] = True

def check():
    for start in range(n):
        k = start
        for i in range(h):
            if bridge[i][k]:
                k +=1
            elif k >0 and bridge[i][k-1]:
                k-=1
        if start != k:
            return False
    return True

def bf(cnt, x,y):
    global ans
    if check():
        ans = min(ans,cnt)
        return
    elif cnt == 3 or ans <= cnt:
        return

    for i in range(x,h):
        k = y if i == x else 0
        for j in range(k,n-1):
            if not bridge[i][j] and not bridge[i][j+1]:
                bridge[i][j] = True
                bf(cnt+1,i,j+2)
                bridge[i][j] = False

ans = 4
bf(0,0,0)
print(ans if ans<4 else -1)