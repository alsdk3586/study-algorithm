import collections

def solution(progresses, speeds):
    answer = []
    progresses = collections.deque(progresses)
    speeds = collections.deque(speeds)
    
    while progresses:
        count = 0
        
        for i in range(len(progresses)):
            progresses[i] += speeds[i]
        
        while progresses:
            progress = progresses.popleft()

            if progress > 99:
                count += 1
                speeds.popleft()   
            else:
                progresses.appendleft(progress)
                break
            
        if count > 0:
            answer.append(count)
    return answer