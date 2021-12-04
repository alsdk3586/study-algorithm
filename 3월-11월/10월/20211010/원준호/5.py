def solution(sizes):
    max_min = 0
    max_max = 0
    for i in range(len(sizes)):
        max_min = max(max_min, min(sizes[i]))
        max_max = max(max_max, max(sizes[i]))

    return max_min * max_max
