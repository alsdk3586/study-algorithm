import sys

def isPalindrome(candidate, s_idx, e_idx, isFirstDepth):
    result = 0
    
    #검사가 끝날때까지 돌린다
    while(s_idx<e_idx):
        #같으면 다음문자로
        if candidate[s_idx] == candidate[e_idx] :
            s_idx += 1
            e_idx -= 1
        #다른데 처음 틀린거면
        elif isFirstDepth:
            #앞뒤로 한칸씩 조지면서 팔린드롬 체크
            result = isPalindrome(candidate, s_idx+1, e_idx, False)
            if result == 2:
                result = isPalindrome(candidate, s_idx, e_idx-1, False)
            
            #맞으면 유사 팔린드롬
            if result == 0:  
                result = 1
            
            break;
        #그 안 뎁스에서 틀리면 바로 리턴
        else:
            result = 2
            break
          
    return result



n = int(input().rstrip())
answer = []

for _ in range(n):
    candidate = list(input().rstrip())
    
    idx = [0, len(candidate)-1];
    result = isPalindrome(candidate, idx[0], idx[1], True);
    answer.append(result)

print("\n".join(map(str,answer)))