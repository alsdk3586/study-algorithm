import heapq

T = int(input())

for _ in range(T):
	N = int(input())
	files = list(map(int, input().split(" ")))
	heapq.heapify(files)
	answer = 0
	while len(files) > 1:
		a = heapq.heappop(files)
		b = heapq.heappop(files)
		answer += (a+b)
		heapq.heappush(files, a+b)

	print(answer)
