N = int(input())


answer = []

def go(num):
    global answer
    for i in range(int(num[-1])-1, -1, -1):
        go(num+str(i))

    answer.append(int(num))
    return num

for i in range(10):
    go(str(i))

answer.sort()
if N >= len(answer):
    print(-1)
else:
    print(answer[N])
