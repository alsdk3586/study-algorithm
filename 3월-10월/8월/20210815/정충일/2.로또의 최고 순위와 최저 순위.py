def solution(lottos, win_nums):
    answer = []
    zero_count = 0
    win_count = 0
    for i in range(len(lottos)):
        if(not lottos[i]): zero_count+=1 #0이 몇개인가!
    for i in range(len(win_nums)):
        for j in range(len(win_nums)):
            if(lottos[i] == win_nums[j]): win_count+=1 #같은 숫자 체킹
    if(not win_count): #범위 안에 들기 위해 count up
        win_count+=1
        if(zero_count == 6): zero_count-=1 #에외
    answer.append(7-(win_count+zero_count)) #결과 입력
    answer.append(7-win_count)
    return answer