import sys

#최대 거리는 10000
vertexNum, edgeNum = map(int, input().rstrip().split(' '))
edges = [[10001]*vertexNum for i in range(vertexNum)]

#마을간 거리 입력
for _ in range(edgeNum):
    start, end, cost = map(int, input().rstrip().split(' '))
    edges[start - 1][end - 1] = cost

#플로이드 와셜
for k in range(vertexNum): 
    for i in range(vertexNum): 
        for j in range(vertexNum):
            edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j])

minCycle = 10001;
#사이클이 생긴 마을간 최소 거리 추출
for i in range(vertexNum):
    minCycle = min(edges[i][i], minCycle)

if minCycle==10001:
    print(-1) 

print(minCycle)