from collections import deque

def solution(enter, leave):
    result = [0] * (len(enter)+1)
    enter, leave = deque(enter), deque(leave)
    stack = []

    while leave:
        if not stack:
            stack.append(enter.popleft())
        
        while enter and leave[0] not in stack:
            stack.append(enter.popleft())
        
        N = leave.popleft()
        stack.remove(N)

        for s in stack:
            if s != N:
                result[N] +=1
                result[s] +=1
    return result[1:]