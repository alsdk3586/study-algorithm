N, K = map(int, input().split())

num = list(input())

delK=K

result = []

for i in range(N):
    while delK and result:
        if result[-1] < num[i]:
            result.pop()
            delK-=1
        else:
            break
    result.append(num[i])

print(''.join(result[:N-K]))