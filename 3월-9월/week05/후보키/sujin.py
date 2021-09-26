from itertools import combinations

def solution(relation):
    n_col, n_row = len(relation[0]), len(relation)
    
    # combinations으로 인덱스 조합을 구함
    candidates = []
    for i in range(1, n_col + 1):
        candidates.extend(combinations(range(n_col), i))
    
    # 유일성을 만족하는 키를 구함
    uniqueKeys = []
    for keys in candidates:
        temp = [tuple(relation_tuple[key] for key in keys) for relation_tuple in relation]
        print(temp)
        if len(set(temp)) == n_row:
            uniqueKeys.append(keys)
    
    # 최소성을 만족시키는 키를 구함
    candidateKeys = set(uniqueKeys)
    for i in range(len(uniqueKeys)):
        for j in range(i + 1, len(uniqueKeys)):
            if all(commonKey in uniqueKeys[j] for commonKey in uniqueKeys[i]):
                candidateKeys.discard(uniqueKeys[j])
    return len(candidateKeys)
