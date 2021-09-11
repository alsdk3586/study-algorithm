from itertools import combinations

N, L, R, X = map(int, input().split())
difficulty = list(map(int, input().split()))
count = 0

for i in range(2,N+1):
    difficultyComb = list(combinations(difficulty,i))
    for j in difficultyComb:
        if L<=sum(j)<= R and max(j)-min(j) >= X:
            count+=1
    
print(count)