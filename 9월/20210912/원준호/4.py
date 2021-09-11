from itertools import combinations

N,L,R,X = map(int, input().split(" "))

problems = list(map(int, input().split(" ")))

answer = 0
for i in range(2, N+1):
    cases = list(combinations(problems, i))

    for case in cases:
        if L <= sum(case) <= R:
            if max(case) - min(case) >= X:
                answer += 1

print(answer)
