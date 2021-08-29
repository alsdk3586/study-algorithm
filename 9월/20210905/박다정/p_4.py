n = int(input())
result = [i for i in range(10)]
numbers = [str(i) for i in range(10)]
start = [str(i) for i in range(1, 10)]


def rec(index, number):
    for i in range(0, index):
        next_number = number + numbers[i]
        result.append(int(next_number))
        rec(i, next_number)


for i in range(len(start)):
    rec(int(start[i]), start[i])

result.sort()

if len(result) < n:
    print(-1)
else:
    print(result[n])
