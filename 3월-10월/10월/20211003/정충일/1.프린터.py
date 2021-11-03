from collections import deque

def solution(priorities, location):
    answer = 0

    point = deque(priorities)

    for i in range(len(priorities)):
        if i!=location:
            point.append((point.popleft(),0))
        else:
            point.append((point.popleft(),1))

    priorities.sort()
    
    while True:
        if priorities[-1] != point[0][0]:
            point.append(point.popleft())
        else:
            if point[0][1] == 1:
                answer+=1
                break
            else:
                priorities.pop()
                point.popleft()
                answer+=1
    
    return answer