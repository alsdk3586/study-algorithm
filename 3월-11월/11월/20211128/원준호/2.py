N, K = map(int, input().split(" "))

items = [[0,0]]
for _ in range(N):
	items.append(list(map(int, input().split(" "))))

dp = [[0 for _ in range(K+1)] for _ in range(N+1)]

items.sort()
for i in range(1, N+1):

	for j in range(K+1):
		if items[i][0] > j:
			dp[i][j] = dp[i-1][j]
		else:
			dp[i][j] = max(dp[i-1][j-items[i][0]] + items[i][1], dp[i-1][j])

print(dp[N][K])
