from itertools import combinations 

def solution(numbers, target):
    indexs = [i for i in range(len(numbers))]
    cases = []
    answer = 0
    
    for i in range(1, len(numbers) + 1):
        cases += combinations(indexs, i)
    for case in cases:
        tmp = numbers[:]
        for i in case:
            tmp[i] *= -1
        if sum(tmp) == target:
            answer += 1
    
    return answer


def dfs(numbers, target, current):
    if sum(numbers) == target:
        return [numbers]
    
    result = []
    
    for i in range(current, len(numbers)):
        tmp = numbers[:]
        tmp[i] *= -1
        result += dfs(tmp, target, i + 1)

    return result

def solution(numbers, target):
    answer = dfs(numbers, target, 0)
    return len(answer)
    