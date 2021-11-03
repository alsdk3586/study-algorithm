def check_same_direction_left(gears, current_index):
    start = 0

    for i in range(current_index, 0, -1):
        if gears[i][6] == gears[i-1][2]:
            return i
    return start

def check_same_direction_right(gears, current_index):
    end = 3

    for i in range(current_index, len(gears)-1):
        if gears[i][2] == gears[i+1][6]:
            return i
    return end

def rotate_left(gear):
    tmp = gear[-1]

    for i in range(len(gear)-1, -1, -1):
        original = gear[i]
        gear[i] = tmp
        tmp = original
    gear[-1] = tmp

def rotate_right(gear):
    tmp = gear[0]

    for i in range(len(gear)):
        original = gear[i]
        gear[i] = tmp
        tmp = original
    gear[0] = tmp

def rotate_gears_left(gears, gear_index, direction):
    end = check_same_direction_left(gears, gear_index)
    for i in range(gear_index-1, end-1, -1):
        if direction == 1:
            rotate_right(gears[i])
        else:
            rotate_left(gears[i])
        direction *= -1

def rotate_gears_right(gears, gear_index, direction):
    end = check_same_direction_right(gears, gear_index)

    for i in range(gear_index+1, end+1):
        if direction == 1:
            rotate_right(gears[i])
        else:
            rotate_left(gears[i])
        direction *= -1

def main(gears, n, rotations):
    answer = 0

    for rotation in rotations:
        gear_index, direction = rotation
        
        rotate_gears_right(gears, gear_index-1, direction * -1)
        rotate_gears_left(gears, gear_index-1, direction * -1)

        if direction == 1:
            rotate_right(gears[gear_index-1])
        else:
            rotate_left(gears[gear_index-1])

    for number in range(4):
        if gears[number][0] == 1:
            answer += 2 ** number
    return answer
if __name__ == '__main__':
    gears = [list(map(int, input())) for _ in range(4)]
    n = int(input())
    rotations = [list(map(int, input().split())) for _ in range(n)]
    print(main(gears, n, rotations))