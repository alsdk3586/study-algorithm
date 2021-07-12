import sys
import collections

input = sys.stdin.readline

n, d, k, c = map(int, input().rstrip().split(' '))
sushis = collections.deque([int(input().rstrip()) for _ in range(n)])
result = collections.deque([])
dic = {}
answer = 0

# 초밥 전체를 순회한다. 먼저 초밥들을 k개까지 모으고 다음 초밥부터
# 가장 오래된 초밥을 제거하고 다음 초밥을 추가
# dictionary를 이용하여 초밥 종류와 갯수를 기록해서 초밥이 queue 새로 반영될 때마다
# dictionary에도 똑같이 반영. 그리고 반영할 때 마다 그때의 초밥 종류를 갱신해준다.

# 초밥 k개를 모은다
for i in range(k):
    result.append(sushis[i])

    if sushis[i] not in dic:
        dic[sushis[i]] = 1
    else:
        dic[sushis[i]] += 1

answer = len(dic.keys())

# 초밥이 한바퀴 돌때까지 가장 오래된 초밥을 맨 뒤에 이동하고 다음 초밥을 넣는다
for i in range(n):
    # 초밥 회전
    tmp = sushis.popleft()
    sushis.append(tmp)
    # 현재 가지고 있는 연속된 k개의 초밥에서 오래된(가장 앞에 있는) 초밥 제거
    tmp1 = result.popleft()
    
    # 수정된 내용을 dictionary에 반영
    if dic[tmp1] == 1:
        del dic[tmp1]
    else:
        dic[tmp1] -= 1

    if sushis[k - 1] in dic:
        dic[sushis[k - 1]] += 1
    else:
        dic[sushis[k - 1]] = 1
    # 현재 가지고 있는 k개의 초밥에 다음 초밥을 추가
    result.append(sushis[k - 1])
    
    # 쿠폰 확인
    if c in dic:
        answer = max(answer, len(dic.keys()))
    else:
        answer = max(answer, len(dic.keys()) + 1)

print(answer)
