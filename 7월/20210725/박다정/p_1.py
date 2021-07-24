import sys
import collections

input = sys.stdin.readline

n = int(input().rstrip())
spaces = [list(map(int, input().rstrip().split(' '))) for _ in range(n)]
deltas = [(-1, 0), (0, -1), (1, 0), (0, 1)]


def bfs(x, y):
    queue = collections.deque([[x, y]])
    weight = 2
    result = 0
    eat = 0

    while queue:
        # 현재 위치 및 물고기 탐색 관련 초기화
        r, c = queue.popleft()
        fishes = []
        visied = [[False for _ in range(n)] for _ in range(n)]

        q = collections.deque([[r, c, 0]])
        # 현재 위칯에서 잡을 수 있는 모든 물고기 탐색
        while q:
            c_r, c_c, c_time = q.popleft()

            for delta in deltas:
                dx, dy = delta
                next_x, next_y = c_r + dx, c_c + dy
                # 맵을 벗어나지 않고 현재 무게보다 같거나 작은 물고기 또는 없는 칸으로 이동
                if -1 < next_x < n and -1 < next_y < n and not visied[next_x][next_y] and weight >= spaces[next_x][
                    next_y]:
                    visied[next_x][next_y] = True

                    if spaces[next_x][next_y] == 0 or spaces[next_x][next_y] == weight:
                        q.append([next_x, next_y, c_time + 1])
                        continue

                    fishes.append([next_x, next_y, c_time + 1])
        # 정렬기준 1.거리 2. 상하 3. 좌우
        fishes.sort(key=lambda x: (x[2], x[0], x[1]))

        # 더 이상 잡을 수 있는 물고기가 없어서 엄마 상어 호출
        if len(fishes) == 0:
            break
        # 조건에 맞는 물고기를 처리
        next_x, next_y, time = fishes[0]
        spaces[next_x][next_y] = 0
        eat += 1
        # 무게를 조건에 맞게 갱신
        if eat == weight:
            weight += 1
            eat = 0

        result += time
        # 물고기 잡은 위치를 시작으로 반복하기 위해
        queue.append([next_x, next_y])
    return result


def main():
    x, y = 0, 0
    result = 0

    for i in range(len(spaces)):
        for j in range(len(spaces)):
            if spaces[i][j] == 9:
                x, y = i, j
                spaces[i][j] = 0
                result = bfs(x, y)
                break
    print(result)


if __name__ == '__main__':
    main()
