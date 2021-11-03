import itertools

n, l, r, x = map(int, input().split(' '))
numbers = list(map(int, input().split(' ')))
case = []

for i in range(2, len(numbers) + 1):
    case += list(itertools.combinations(numbers, i))

result = list(filter(lambda p: max(p) - min(p) >= x, list(filter(lambda p: l <= sum(p) <= r, case))))

print(len(result))
