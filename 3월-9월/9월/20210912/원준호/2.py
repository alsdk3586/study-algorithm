N = int(input())

stair = []
for _ in range(N):
    stair.append(int(input()))

# ??xoo     dp[i] = dp[i-1] + stair[i]
# ??oxo     dp[i] = dp[i-2] + stair[i]

if N == 1:
    print(stair[0])
elif N == 2:
    print(stair[0]+stair[1])
else:
    dp = [[0 for _ in range(2)] for _ in range(N)]

    dp[0][0] = stair[0]
    dp[0][1] = stair[0]
    dp[1][0] = stair[1]
    dp[1][1] = stair[0] + stair[1]

    for i in range(2, N):
        dp[i][0] = max(dp[i-2][0] + stair[i], dp[i-2][1] + stair[i])
        dp[i][1] = dp[i-1][0] + stair[i]

    print(max(dp[N-1][0], dp[N-1][1]))
