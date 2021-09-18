def solution(weights, head2head):
    N = len(weights)
    # 승률 (큰) => 자신보다 무거운 복서 이긴 횟수 (큰) => 몸무게 (큰) => 번호 (작)   
    win_rate = [None] * N
    for i in range(N):
        win = 0
        lose = 0
        big_win = 0
        for j in range(N):
            if head2head[i][j] == "L":
                lose += 1
            elif head2head[i][j] == "W":
                win += 1
                if weights[i] < weights[j]:
                    big_win += 1
        
        if (win + lose) == 0:
            win_rate[i] = (0, 0, weights[i], -i-1)
        else:
            win_rate[i] = (win/(win+lose), big_win, weights[i], -i-1)
        
    win_rate.sort(reverse=True)
    answer = []
    for ws in win_rate:
        answer.append(-ws[3])
    
    return answer
