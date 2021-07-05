import sys

input = sys.stdin.readline

n = int(input().rstrip())
left_large_height_counts = list(map(int, input().rstrip().split(' ')))
result = [0 for _ in range(n)]
prev_index = 0

for i in range(n):
    count = left_large_height_counts[i] + 1
    index = 0

    for j in range(n):
        if not count:
            break
        if not result[j]:
            count -= 1
            index = j

    if not result[index] and index > prev_index:
        result[index] = i + 1
        prev_index = index
        continue

    for j in range(n):
        if not result[j]:
            result[index] = i + 1
            prev_index = index
            break

print(*result)
