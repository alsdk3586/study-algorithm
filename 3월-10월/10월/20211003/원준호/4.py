N, K = map(int, input().split())

number = input()

stack = [number[0]]

for n in number[1:]:
    if stack[-1] < n:
        while stack and K > 0:
            if stack[-1] < n:
                stack.pop()
                K -= 1
            else:
                break
    stack.append(n)

if K > 0:
    stack = stack[:-K]
print("".join(stack))
