def solution(lottos, win_nums):
    rank = [6,6,5,4,3,2,1]
    right = 0
    zero = 0
    for num in lottos:
        # 맞는 번호 개수
        if num in win_nums:
            right += 1
        # 맞을 수도, 틀릴 수도 있는 번호 개수
        if num == 0:
            zero += 1
    
    return [rank[right+zero], rank[right]]
