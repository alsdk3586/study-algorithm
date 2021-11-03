import math
def solution(progresses, speeds):
    days =[]
    N = len(speeds)
    for i in range(N):
        days.append(math.ceil((100-progresses[i]) / speeds[i]))
    
    answer = []
    now_day = days[0]
    num = 1
    for i in range(1, N):
        if now_day >= days[i]:
            num += 1
        else:
            answer.append(num)
            now_day = days[i]
            num = 1
    
    answer.append(num)
    
    return answer
    
