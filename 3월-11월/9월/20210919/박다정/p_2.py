def solution(weights, head2head):
    result = []

    for i in range(len(head2head)):
        win_count = 0
        win_weight_count = 0
        match_count = 0
        tmp = [i + 1]

        for j in range(len(head2head)):
            if i == j:
                continue
            if head2head[i][j] == 'N':
                continue
            if head2head[i][j] == 'W':
                win_count += 1
                if weights[i] < weights[j]:
                    win_weight_count += 1
            match_count += 1

        if match_count > 0:
            tmp.append(win_count / match_count)
        else:
            tmp.append(0)
        tmp.append(win_weight_count)
        tmp.append(weights[i])
        result.append(tmp)

    result.sort(key=lambda x: (-x[1], -x[2], -x[3], x[0]))

    return list(map(lambda x: x[0], result))