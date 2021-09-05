tmp = []

def rec(r, vowel, current):
    
    if len(current) == r:
        tmp.append(''.join(current))
        return
    
    for v in vowel:
        current.append(v)
        # print(current)
        rec(r, vowel, current)
        current.pop()
    
def solution(word):
    answer = 1
    vowel = ['A', 'E', 'I', 'O', 'U']
    result = []
    
    for i in range(1, 6):
        rec(i, vowel, [])
    
    tmp.sort()
    
    for i, v in enumerate(tmp):
        if v == word:
            return i + 1
    
    return answer
