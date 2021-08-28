def solution(record):
    answer = []
    user = {}

    for message in record:
        m = message.split(' ')
        if m[0] != 'Leave': #나가는 경우 제외 user 넣기
            user[m[1]] = m[2]

    for message in record:
        m = message.split(' ')
        if m[0] == 'Enter': #들어옴 출력
            answer.append(user[m[1]]+"님이 들어왔습니다.")
        elif m[0] == 'Leave': #나감 출력
            answer.append(user[m[1]]+"님이 나갔습니다.")

    return answer