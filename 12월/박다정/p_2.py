def solution(n, times):
    times.sort()
    answer = times[-1] * n
    start = 1
    end = answer
    
    while start <= end:
        middle = (start + end) // 2
        currentTime = 0
        
        for time in times:
            currentTime += middle // time
            
        if currentTime < n:
            start = middle + 1
        else:
            if answer > middle:
                answer = middle
            end = middle - 1
    
    return answer