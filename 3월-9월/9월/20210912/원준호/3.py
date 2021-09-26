# 극 같으면 그대로, 다르면 반시계
# N = 0, S = 1
# 좌 : 6, 우 : 2

def rotate(idx, direction):
    if direction == 1:
        gears[idx] = [gears[idx][-1]] + gears[idx][:-1]
    else:
        gears[idx] = gears[idx][1:] + [gears[idx][0]]
    return

gears = []
for _ in range(4):
    gears.append(list(map(int, input())))

K = int(input())

actions = []
for _ in range(K):
    num, direction = map(int, input().split(" "))
    num -= 1
    rotate_list = [(num, direction)]

    # 왼쪽 체크
    i = num
    next_direction = direction
    while 0 < i:
        if gears[i-1][2] == gears[i][6]:
            break
        next_direction = - next_direction
        rotate_list.append((i-1, next_direction))
        i -= 1

    # 오른쪽 체크
    i = num
    next_direction = direction
    while i < 3:
        if gears[i][2] == gears[i+1][6]:
            break
        next_direction = - next_direction
        rotate_list.append((i+1, next_direction))
        i += 1

    for num, direction in rotate_list:
        rotate(num, direction)

print(gears[0][0] * 1 + gears[1][0] * 2 + gears[2][0] * 4 + gears[3][0] * 8)
