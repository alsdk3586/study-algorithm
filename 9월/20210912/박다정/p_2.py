n = int(input())
stairs = [int(input()) for _ in range(n)]
table = [[0, 0] for _ in range(n)]

table[0] = [stairs[0], stairs[0]]

if n > 1:
    table[1] = [stairs[0] + stairs[1], stairs[1]]

for i in range(2, n):
    table[i][0] = table[i - 1][1] + stairs[i]
    table[i][1] = max(table[i - 2]) + stairs[i]

print(max(table[-1]))
