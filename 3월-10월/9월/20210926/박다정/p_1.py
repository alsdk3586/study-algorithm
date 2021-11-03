def solution(enter, leave):
    result = [set() for _ in range(len(enter))]
    
    for i in range(len(enter)):
        current = leave.index(enter[i])
        
        # 먼저 들어온 사람이 나가기 전에 있으면 카운트
        prev_enter_person = enter[:i]
        prev_leave_person = leave[:current]
        
        for person in prev_enter_person:            
            if person not in prev_leave_person or len(prev_leave_person) == 0:
                result[enter[i]-1].add(person)
                result[person-1].add(enter[i])
        
        # 나보다 먼저 나간 사람이 나보다 늦게 입장했을 때
        after_enter_person = enter[i+1:]
        prev_leave_person = leave[:current]
        min_index = 1000
        
        for after_person in after_enter_person:
            if after_person in prev_leave_person:
                min_index = min(min_index, leave.index(after_person))

        for person in leave[min_index:current]:
            result[enter[i]-1].add(person)
            result[person-1].add(enter[i])

    return list(map(lambda x: len(x), result))
