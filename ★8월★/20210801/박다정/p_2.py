import collections


def solution(enroll, referral, seller, amount):
    tmp = {}
    dic = {}
    answer = []

    # 역순으로 그래프 생성
    for i in range(len(enroll) - 1, -1, -1):
        dic[enroll[i]] = []
        tmp[enroll[i]] = 0

        if referral[i] != '-':
            dic[enroll[i]].append(referral[i])
    # bfs 순회
    for i in range(len(seller)):

        if seller[i] == 0:
            continue

        queue = collections.deque([seller[i]])
        result = amount[i] * 100

        while queue:
            current = queue.popleft()
            fee = result * 0.1
            # 10%가 1원 미만일 경우 10% 제외하지 않고 더함
            if fee < 1:
                tmp[current] += result
                continue
            else:
                # 원 단위로 절삭 int(number)
                tmp[current] += result - int(fee)
                result = int(fee)
            # 연결된 노드가 있는지 확인
            if not dic[current]:
                continue
            queue.append(dic[current][0])

    # 결과 값 넣기
    for e in enroll:
        answer.append(tmp[e])

    return answer