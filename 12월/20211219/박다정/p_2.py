import sys

input = sys.stdin.readline
n, m = map(int, input().rstrip().split(' '))
result = [1 for _ in range(n)]
subjects = [list(map(int, input().rstrip().split(' '))) for _ in range(m)]
subjects.sort()

for subject in subjects:
    a, b = subject
    result[b - 1] = max(result[a - 1] + 1, result[b - 1])

print(*result)
