import sys

V, E = map(int, sys.stdin.readline().split())
INF = 999999
arr = [[INF] * V for i in range(V)] #길 없음을 표시
for i in range(E):
    x, y, z = map(int, sys.stdin.readline().split())
    arr[x-1][y-1] = z #길 있음을 표시
#플로이드 와샬
for k in range(V): # k = 거쳐가는 노드
    for i in range(V): # i = 출발 노드
        for j in range(V): # j = 도착 노드
            if arr[i][j] > arr[i][k] + arr[k][j]: #더 작은 값
                arr[i][j] = arr[i][k] + arr[k][j]
result = INF #초기화
for i in range(V): #다시 시작점으로 돌아온 값 중 가장 작은 값 갱신
    result = min(result,arr[i][i])
if result == INF: print(-1) #결과 출력
else: print(result)