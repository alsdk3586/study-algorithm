from itertools import combinations
from bisect import bisect_left

# https://tech.kakao.com/2021/01/25/2021-kakao-recruitment-round-1/
# https://velog.io/@djagmlrhks3/Algorithm-Programmers-%EC%88%9C%EC%9C%84-%EA%B2%80%EC%83%89-by-Python

# 사용자 정보의 모든 경우의 수를 저장
# example) -----, backend----, ...
def create_all_case(info):
    case = [0, 1, 2, 3]
    result = []
    for i in range(0, 5):
        for numbers in combinations(case, i):
            tmp = ''
            for j in case:
                if j not in numbers:
                    tmp += '-'
                else:
                    tmp += info[j]
            result.append(tmp)       
    return result
    
    
def solution(info, query):
    answer = []
    dic = {}
    # 지원자 정보의 모든 경우의 수를 dictionary에 저장
    for i in info:
        stats = i.split(' ')
        cases = create_all_case(stats)
        
        for case in cases:
            if case not in dic:
                dic[case] = [int(stats[-1])]
            else:
                dic[case].append(int(stats[-1]))
    # 각 경우의 수에 포함되는 점수들을 정렬
    for _, value in dic.items():
        value.sort()
    # 질문에 해당하는 정보를 찾기
    for q in query:
        # dictionary에 저장된 형태로 수정
        q = q.split(' and ')
        food, score = q[-1].split(' ')
        score = int(score)
        q[-1] = food
        q = ''.join(q)
        # 질문에 해당하는 지원자들이 있다면 목표 점수에 미달하는 점수의 수를 구하고 전체 수를 뺀다
        if q in dic:
            answer.append(len(dic[q]) - bisect_left(dic[q], score, 0, len(dic[q])))
        else:
            answer.append(0)

    return answer