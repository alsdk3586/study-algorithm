from collections import deque

N, X = map(int, input().split(" "))

visitors = list(map(int, input().split(" ")))

summation = sum(visitors[:X])
answer = summation
answer_cnt = 1
for i in range(X , N):
	summation = summation - visitors[i-X] + visitors[i]
	if summation > answer:
		answer = summation
		answer_cnt = 1
	elif summation == answer:
		answer_cnt += 1

if answer == 0:
	print("SAD")
else:
	print(answer)
	print(answer_cnt)
