import sys

def solution(lottos, win_nums):
    answer = []
    #정렬부터 하고
    lottos.sort()
    win_nums.sort()
    
    num_true = 0;
    num_deleted = 0;
    
    i=0; j=0;
    #한쪽이 끝날때까지 체크
    while i<6 and j<6:
        #같으면 맞는 번호 +1
        if win_nums[i]==lottos[j]:
            num_true += 1
            i += 1
            j += 1
        #다르면 
        else:
            # 지워진 번호면 지워진 번호 +1
            if lottos[j]==0:
                num_deleted +=1;
            
            #다음칸으로 넘어가기
            if lottos[j] < win_nums[i]:
                j += 1
            elif win_nums[i]<lottos[j]:
                i += 1
                
    
    worstRank = 7-num_true
    bestRank = 7-num_true-num_deleted
    
    #아 여기 지저분한데...
    if worstRank==7:
        worstRank=6;
    if bestRank==7:
        bestRank=6;
    
    answer.append(bestRank)
    answer.append(worstRank)
    return answer


lottos = map(int, input().rstrip())
win_nums = map(int, input().rstrip())

solution(lottos, win_nums)