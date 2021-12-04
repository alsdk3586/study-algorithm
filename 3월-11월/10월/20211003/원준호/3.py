from collections import deque

T = int(input())

for _ in range(T):
    log = input()
    log = log.strip("<>")

    left = deque()
    right = deque()

    for char in log:
        if char.isalnum():
            left.append(char)

        elif char == "<" and left:
            right.appendleft(left.pop())

        elif char == ">" and right:
            left.append(right.popleft())

        elif char == "-":
            # if right:
            #     right.popleft()
            if left:
                left.pop()

    print("".join(left+right))
