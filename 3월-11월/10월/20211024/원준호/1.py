def solution(answers):
    N = len(answers)
    answer_cnt = [0,0,0]
    
    one = [1,2,3,4,5]
    one_idx = 0
    for i in range(N):
        answer_cnt[0] += int(one[one_idx] == answers[i])
        one_idx = (one_idx+1)%5
    
    two = [1,3,4,5]
    two_idx = 0
    for i in range(N):
        if i % 2 == 0:
            answer_cnt[1] += int(2 == answers[i])
        else:
            answer_cnt[1] += int(two[two_idx] == answers[i])
            two_idx =  (two_idx+1)%4
    
    three = [3,1,2,4,5]
    three_idx = -1
    for i in range(N):
        if i % 2 == 0:
            three_idx =  (three_idx+1)%5
        answer_cnt[2] += int(three[three_idx] == answers[i])
    
    
    answer = []
    for idx, cnt in enumerate(answer_cnt, start=1):
        if cnt == max(answer_cnt):
            answer.append(idx)
    
    return answer
    
