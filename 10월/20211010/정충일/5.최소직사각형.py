def solution(sizes):
    sizes=[sorted(i) for i in sizes]
    maxWidth = [i[0] for i in sizes]
    maxLength = [i[1] for i in sizes]
    return max(maxWidth) * max(maxLength)
