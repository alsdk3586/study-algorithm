import collections

def solution(enroll, referral, seller, amount):
    tmp = {}
    dic = {}
    answer = []
    
    for i in range(len(enroll)-1, -1, -1):
        dic[enroll[i]] = []
        tmp[enroll[i]] = 0
        
        if referral[i] != '-':
            dic[enroll[i]].append(referral[i])
    
    for i in range(len(seller)):
        
        if seller[i] == 0:
            continue
        
        queue = collections.deque([seller[i]])
        result = amount[i] * 100
        
        while queue:
            current = queue.popleft()
            # 원 단위로 절삭
            fee = result * 0.1
            # 10%가 1원 미만일 경우 10% 제외하지 않고 더함
            if fee < 1:
                tmp[current] += result
                continue
            else:
                tmp[current] += result - int(fee)
                result = int(fee)
            
            if not dic[current]:
                continue
            queue.append(dic[current][0])
            
    for e in enroll:
        answer.append(tmp[e])
    
    
    return answer