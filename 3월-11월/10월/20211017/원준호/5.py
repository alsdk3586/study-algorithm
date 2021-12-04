from collections import defaultdict
def solution(n, wires):
    answer = -1
    graph = defaultdict(list)
    for x,y in wires:
        graph[x].append(y)
        graph[y].append(x)
    
    def dfs(now):
        visited[now] = True
        ret = 0
        for next in graph[now]:
            if visited[next] == None:
                ret += dfs(next)
        return ret + 1
    
    answer = float("inf")
    for x,y in wires:
        graph[x].remove(y)
        graph[y].remove(x)
        visited = [None] * (n+1)
        answer = min( abs(dfs(x) - dfs(y)), answer)
        graph[x].append(y)
        graph[y].append(x)
    
    return answer
