import sys

N, M, K = map(int, sys.stdin.readline().split())

graph = [[] for _ in range(N+1)]
build = [0]*(N+1)
indegree = [0]*(N+1)
flag = False

for _ in range(M):
    i, j= map(int, sys.stdin.readline().split())
    graph[i].append(j)
    indegree[j]+=1

for _ in range(K):
    command, building = map(int, sys.stdin.readline().split())
    if command == 1:
        if indegree[building]:
            flag = True
            break

        build[building]+=1

        if build[building] == 1:
            for i in graph[building]:
                indegree[i]-=1
    else:
        if build[building] <= 0:
            flag = True
            break

        build[building]-=1

        if not build[building]:
            for i in graph[building]:
                indegree[i]+=1

if flag:
    print("Lier!")
else:
    print("King-God-Emperor")