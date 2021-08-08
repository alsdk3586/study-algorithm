# 입력 값이 적어서 브루트 포스 시도

def solution(lottos, win_nums):
    answer = []
    zero_count = 0
    tmp1 = 0
    ranking = {
        6 : 1,
        5 : 2,
        4 : 3,
        3 : 4,
        2 : 5
    }
    # 로또 번호 가운데 알 수 없는 번호와
    # 맞춘 번호를 탐색
    for lotto in lottos:
        if lotto == 0:
            zero_count += 1
        elif lotto in win_nums:
            tmp1 += 1
    # 최고의 순위를 얻으려면 알수 없는 번호가 전부 맞는 번호
    if tmp1 + zero_count in ranking:
        answer.append(ranking[tmp1+zero_count])
    else:
        answer.append(6)
    # 가장 낮은 순위는 알 수 없는 번호가 전부 틀린 번호
    if tmp1 in ranking:
        answer.append(ranking[tmp1])
    else:
        answer.append(6)
    return answer
