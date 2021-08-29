def solution(table, languages, preference):
    answer = {}
    rank = {}
    
    # table 값 초기화
    for t in table:
        kind = t.split(' ')
        industry = kind[0]
        rank[industry] = {}
        answer[industry] = 0
        
        for i in range(1, len(kind)):
            rank[industry][kind[i]] = 6 - i
    # 산업별 점수 계산
    for i in range(len(languages)):
        for k, value in rank.items():
            # 산업별로 존재하지 않는 언어가 존재한다
            if languages[i] in value:
                answer[k] += value[languages[i]] * preference[i]
    
    # 점수, 이름순으로 정렬
    answer = sorted(answer.items(), key=lambda x: (-x[1], x[0]))

    return answer[0][0]