import sys

input = sys.stdin.readline

h, w = map(int, input().rstrip().split(' '))
blocks = list(map(int, input().rstrip().split(' ')))
result = 0

# 기준점 좌우로 구하기 때문에 1과 w -1이 경계선
for i in range(1, w - 1):
    left = blocks[i]
    # 현재 기준으로 왼쪽에서 가장 큰 블록 탐색
    for j in range(i - 1, -1, -1):
        if left < blocks[j]:
            left = blocks[j]

    right = blocks[i]
    # 현재 기준으로 오른쪽에서 가장 큰 블록 탐색
    for j in range(i + 1, w):
        if right < blocks[j]:
            right = blocks[j]
    # 두 블록 가운데 가장 작은 블록으로 현재 고이는 양 계산
    result += min(left, right) - blocks[i]

print(result)
