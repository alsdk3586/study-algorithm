n, k = map(int, input().split(' '))
number = list(input())
stack = []

for i in range(len(number)):
    if len(stack) == 0:
        stack.append(number[i])
        continue

    while stack and k > 0:
        current = stack.pop()

        if current >= number[i]:
            stack.append(current)
            break
        k -= 1

    stack.append(number[i])

while k > 0:
    stack.pop()
    k -= 1

print(''.join(stack))
