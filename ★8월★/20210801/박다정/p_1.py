import sys
import collections

input = sys.stdin.readline

n, k = map(int, input().rstrip().split(' '))
wells = list(map(int, input().rstrip().split(' ')))
queue = collections.deque([])
dic = {}
result = 0

# bfs에 사용할 큐 초기화
for well in wells:
    dic[well] = 0
    queue.append((well, 0))

while queue and k > 0:
    current, unlucky = queue.popleft()

    if k > 0 and current - 1 not in dic:
        dic[current - 1] = unlucky + 1
        queue.append((current - 1, unlucky + 1))
        k -= 1

    if k > 0 and current + 1 not in dic:
        dic[current + 1] = unlucky + 1
        queue.append((current + 1, unlucky + 1))
        k -= 1


for _, value in dic.items():
    result += value

print(result)