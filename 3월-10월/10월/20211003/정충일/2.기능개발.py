from collections import deque

def solution(progresses, speeds):
    answer = []
    days = deque()

    for i in range(len(progresses)):
        day=1
        while 100>progresses[i]+speeds[i]*day:
            day+=1
        days.append(day)

    stack = []

    stack.append(days.popleft())
    while days:
        if stack[0] >=days[0]:
            stack.append(days.popleft())
        else:
            answer.append(len(stack))
            stack=[]
            stack.append(days.popleft())
        
    if stack:
        answer.append(len(stack))

    return answer