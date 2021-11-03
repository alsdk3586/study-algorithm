def solution(numbers, hand):
    
    def diff(now, next):
        return abs(now[0]-next[0]) + abs(now[1]-next[1])
    
    pad = [(3,1), (0,0), (0,1), (0,2), (1,0), (1,1), (1,2), (2,0), (2,1), (2,2)]
    left = (3,0)
    right = (3,2)
    answer = ""
    for num in numbers:
        if num in [1,4,7]:
            answer += "L"
            left = pad[num]
        elif num in [3,6,9]:
            answer += "R"
            right = pad[num]
        else:
            left_diff = diff(left, pad[num])
            right_diff = diff(right, pad[num])
            
            if left_diff > right_diff or (left_diff == right_diff and hand == "right"):
                answer += "R"
                right = pad[num]
            elif left_diff < right_diff or (left_diff == right_diff and hand == "left"):
                answer += "L"
                left = pad[num]

    return answer
