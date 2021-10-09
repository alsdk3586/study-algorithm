from collections import deque
def solution(begin, target, words):
    ans=0

    if target not in words:
        return 0
    
    q = deque()
    q.append(begin)
    visited = [0 for _ in words]

    while q:
        x = q.popleft()
        if x == target:
            return ans

        for i in range(len(words)):
            count = 0
            for j in range(len(begin)):
                if x[j] != words[i][j]:
                    count+=1
            if count==1 and not visited[i]:
                q.append(words[i])
                visited[i]=1
                ans+=1
    return ans