T = int(input())

for _ in range(T):
    N = int(input())

    dp = [0] * 100001

    dp[1] = 1
    dp[2] = 2
    dp[3] = 2
    dp[4] = 3
    dp[5] = 3
    dp[6] = 6
    for i in range(7, N+1):
        dp[i] = (dp[i-6] + dp[i-4] + dp[i-2]) % 1000000009

    print(dp[N])
