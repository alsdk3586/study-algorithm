# 모든 건물 중복 건설 가능
# 1건물은 최대 3개의 건물에 영향

# 치트키 = 원하는 건물 짓기
import sys
from collections import defaultdict
input = sys.stdin.readline

N, M, K = map(int, input().split(" "))
graph = defaultdict(list)
in_degrees = [0] * (N+1)
for _ in range(M):
    a, b = map(int, input().split(" "))
    graph[a].append(b)
    in_degrees[b] += 1

answer = True
building_counter = defaultdict(int)
for _ in range(K):
    action, num = map(int, input().split(" "))

    if action == 1:
        # 건설할 수 없는 건물이 건설
        if in_degrees[num] != 0:
            answer = False
            break

        # 처음 짓는다면
        if building_counter[num] == 0:
            for next in graph[num]:
                in_degrees[next] -= 1
        building_counter[num] += 1

    else:
        # 건설한적 없는 건물이 파괴
        if building_counter[num] == 0:
            answer = False
            break

        building_counter[num] -= 1
        # 건물이 모두 지워졌다면
        if building_counter[num] == 0:
            for next in graph[num]:
                in_degrees[next] += 1

if answer:
    print("King-God-Emperor")
else:
    print("Lier!")
