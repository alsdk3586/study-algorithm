from collections import deque
def solution(begin, target, words):
    def check(a,b):
        diff = 0
        for i in range(len(a)):
            if a[i] != b[i]:
                diff += 1
        if diff > 1:
            return False
        else:
            return True

    visited = {}
    def bfs(begin, target):
        queue = deque()
        
        queue.append(begin)
        visited[begin] = 0
        
        while queue:
            now = queue.popleft()
            
            if now == target:
                return visited[target]
            
            for word in words:
                if visited.get(word) == None and check(now, word):
                    queue.append(word)
                    visited[word] = visited[now] + 1
        return 0
        
    return bfs(begin, target)
