import sys
import collections

input = sys.stdin.readline

# 참고 https://jinservice.tistory.com/34

n, k, r = map(int, input().rstrip().split(' '))
# 연결된 다리
bridge = [[[] for _ in range(n)] for _ in range(n)]
# 소의 위치
farm = [[0 for _ in range(n)] for _ in range(n)]
deltas = [(-1, 0), (0, -1), (1, 0), (0, 1)]
cows = []

for _ in range(r):
    r1, c1, r2, c2 = map(int, input().rstrip().split(' '))
    bridge[r1 - 1][c1 - 1].append([r2 - 1, c2 - 1])
    bridge[r2 - 1][c2 - 1].append([r1 - 1, c1 - 1])

for _ in range(k):
    row, column = map(int, input().rstrip().split(' '))
    farm[row - 1][column - 1] = 1
    cows.append([row - 1, column - 1])


def bfs(row, column, cow_numbers):
    visited = [[False for _ in range(n)] for _ in range(n)]
    visited[row][column] = True
    queue = collections.deque([[row, column]])
    count = 0

    while queue:
        x, y = queue.popleft()

        for delta in deltas:
            dx, dy = delta

            next_x = x + dx
            next_y = y + dy
            # 소가 다리를 건너지 않는 경우를 카운트
            if -1 < next_x < len(visited) and -1 < next_y < len(visited) and not visited[next_x][next_y] and (
                    [next_x, next_y] not in bridge[x][y] or bridge[x][y] == []):
                visited[next_x][next_y] = True
                queue.append([next_x, next_y])

                if farm[next_x][next_y] == 1:
                    count += 1
    # 남은 소들에서 다리를 건너지 않는 소들 제외하기
    return (cow_numbers - 1) - count


def main():
    result = 0
    cow_numbers = len(cows)
    while cows:
        x, y = cows.pop()
        result += bfs(x, y, cow_numbers)
        # 중복을 제거하기 위해 현재 소의 위치와 남은 소의 갯수를 갱신
        farm[x][y] = 0
        cow_numbers -= 1

    print(result)


if __name__ == '__main__':
    main()
