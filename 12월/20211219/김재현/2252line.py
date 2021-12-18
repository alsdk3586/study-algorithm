import sys
from collections import deque

n,m=map(int,sys.stdin.readline().split())   #노드(과목)의 수,간선(조건)의 수
indgree=[0]*(n)   #진입차수
graph=[[] for _ in range(n)]  #노드에 연결된 다른 노드를 저장
time=[0]*(n)
for _ in range(m):
    a, b=map(int,sys.stdin.readline().split())
    graph[a].append(b)
    indgree[b]+=1   #진입차수 +1

def line():
    q=deque()   #(연결 노드, 선행 노드 수)
    for i in range(n):  #진입차수 0인 노드 큐에 삽입
        if indgree[i]==0:
            q.append((i,1))
    while q:
        now, t=q.popleft()
        time[now]=t
        for i in graph[now]:    #now 노드와 연결된 다른 노드들 탐색
            indgree[i]-=1   #진입차수 -1
            if indgree[i]==0:
                q.append((i,t+1))
    for i in range(1,len(time)):
        print(time[i],end=' ')

line()