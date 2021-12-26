import collections

NORTH = 0
SOUTH = 2
EAST = 1
WEST = 3

def change_direction(direction):
    return (direction  + 3) % 4

def is_clear_all_direction(row, column, room):
    if room[row+1][column] != 0 and room[row-1][column] != 0 and room[row][column+1] != 0 and room[row][column-1] != 0:
        return True
    return False

def bfs(row, column, direction, room):
    queue = collections.deque()
    queue.append((row, column))
    clean_area_counter = 0

    while queue:
        x, y = queue.popleft()
        location = None
        back_x, back_y = 0,0

        if room[x][y] == 0:
            clean_area_counter += 1
            room[x][y] = -1
        # 방향에 따른 위치 좀 더 깔끔하게 수정
        if direction == NORTH:
            location = [(x, y-1)]
            back_x, back_y = x+1, y
        elif direction == EAST:
            location = [(x-1, y)]
            back_x, back_y = x, y-1
        elif direction == SOUTH:
            location = [(x, y+1)]
            back_x, back_y = x-1, y
        else:
            location = [(x+1, y)]
            back_x, back_y = x, y+1

        for next_x, next_y in location:
            if 0 > next_x or next_x > len(room)-1 or 0 > next_y  or next_y > len(room[0])-1:
                break
            if is_clear_all_direction(x, y, room) and room[back_x][back_y] == 1:
                return clean_area_counter
            elif is_clear_all_direction(x, y, room) and room[back_x][back_y] == -1:
                queue.append((back_x, back_y))
            else:
                if room[next_x][next_y] == 0:
                    queue.append((next_x, next_y))
                else:
                    queue.append((x, y))

                direction = change_direction(direction)
    return clean_area_counter

def main(row, column, direction, room):
    return bfs(row, column, direction, room)

if __name__ == '__main__':
    n, m = map(int, input().split())
    row, column, direction = map(int, input().split())
    room = [list(map(int, input().split())) for _ in range(n)]
    print(main(row, column, direction, room))