from collections import deque

def solution(priorities, location):
    answer = 0
    myRequestPrioritie = priorities[location]
    result = priorities[:]
    result.sort(reverse=True)
    result = deque(result)
    priorities = deque(priorities)
    
    while result:
        if priorities[0] != result[0] and location == 0:
            priorities.append(priorities.popleft())
            location = len(priorities) - 1
        elif priorities[0] == result[0] and location != 0:
            result.popleft()
            priorities.popleft()
            location -= 1
            answer += 1
        elif priorities[0] != result[0] and location != 0:
            priorities.append(priorities.popleft())
            location -= 1
        else:
            return answer + 1
        
        
    return answer