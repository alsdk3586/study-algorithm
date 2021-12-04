from itertools import permutations


def count(k, dungeons):
    answer = 0
    for dungeon in dungeons:
        minimum, consume = dungeon
        if k < minimum:
            return answer
        k -= consume
        answer += 1
    return answer


def solution(k, dungeons):
    answer = []
    shuffled = permutations(dungeons, len(dungeons))

    for s in shuffled:
        answer.append(count(k, s))

    return max(answer)
