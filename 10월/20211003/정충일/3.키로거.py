from collections import deque

N = int(input())

for _ in range(N):
    searchPW = input()

    stack = deque()
    result = deque()

    for i in searchPW:
        if i == "<" :
            if len(result):
                stack.append(result.pop())
        elif i == ">":
            if len(stack):
                result.append(stack.pop())
        elif i == '-':
            if len(result):
                result.pop()
        else:
            result.append(i)

    while stack:
        result.append(stack.pop())

    print("".join(result))