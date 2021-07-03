from itertools import combinations 

def solution(orders, course):
    answer = []
    dic = {}
    t = {}
    
    for order in orders:
        for count in course:
            for result in list(combinations(order, count)):
                result = list(result)
                result.sort()
                tmp = ''.join(result)

                if tmp not in dic:
                    dic[tmp] = 1
                else:
                    dic[tmp] += 1

    for k, v in dic.items():
        if len(k) in course and len(k) not in t or v > t[len(k)][0]:
            t[len(k)] = [v, [k]]
        elif len(k) in course and v == t[len(k)][0]:
            t[len(k)][0] = v
            t[len(k)][1].append(k)

    for k, v in t.items():
        count, recomanded = v
        if count > 1:
            answer += recomanded
    answer.sort()
    return answer