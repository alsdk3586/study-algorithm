from collections import deque, defaultdict

def solution(priorities, location):
    
    papers = defaultdict(int)
    for p in priorities:
        papers[p] += 1
    
    priorities = deque([(idx, val) for idx, val in enumerate(priorities)])
    best = max(priorities, key = lambda x : x[1])
    print(priorities, best)
    answer = []
    while priorities:    
        best = max(priorities, key = lambda x : x[1])
        now = priorities.popleft()
        
        if now[1] == best[1]:
            answer.append(now[0])
    
        else :
            priorities.append(now)
    
    return answer.index(location)+1
