import sys

input = sys.stdin.readline

n, m = map(int, input().rstrip().split(' '))
numbers = list(map(int, input().rstrip().split(' ')))
ranges = [list(map(int, input().rstrip().split(' '))) for _ in range(m)]
table = [0 for _ in range(n + 1)]

for i in range(len(numbers)):
    table[i + 1] = table[i] + numbers[i]

for i in range(len(ranges)):
    start, end = ranges[i]
    print(table[end] - table[start - 1])
