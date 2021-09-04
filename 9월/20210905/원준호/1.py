from collections import defaultdict
def solution(table, languages, preference):
    answer = ''
    
    table = list(map(lambda x : x.split(), table))
    R = len(table)
    C = len(table[0])
    scores = defaultdict(int)

    for i in range(R):
        for j in range(C):
            for l in range(len(languages)):
                if table[i][j] == languages[l]:
                    scores[table[i][0]] += preference[l] * (C-j)
                    
    max_val = -float("inf")
    answer = 0
    for key in sorted(scores.keys()):
        if max_val < scores[key]:
            max_val = scores[key]
            answer = key
    
    return answer
