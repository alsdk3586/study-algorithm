import sys
import collections

input = sys.stdin.readline
deltas = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def bfs(x, y, n, l, r, countrys, visited):
    queue = collections.deque([[x, y]])
    unions = [[x, y]]
    visited[x][y] = True

    while queue:
        c_x, c_y = queue.popleft()

        for delta in deltas:
            dx, dy = delta
            next_x = c_x + dx
            next_y = c_y + dy
            # 상하 좌우로 인구 이동 시작
            if -1 < next_x < n and -1 < next_y < n and not visited[next_x][next_y] and l <= abs(
                    countrys[c_x][c_y] - countrys[next_x][next_y]) <= r:
                visited[next_x][next_y] = True
                queue.append([next_x, next_y])
                unions.append([next_x, next_y])

    result = 0
    # 인구 이동한 결과 합계
    for country in unions:
        r, c = country
        result += countrys[r][c]
    # 인구 이동결과로 인구수 조절
    result = int(result / len(unions))
    # 인구 이동한 결과를 반영
    for country in unions:
        r, c = country
        countrys[r][c] = result


def main(n, l, r, countrys):
    count = 0

    while True:
        tmp = set()
        for i in range(n):
            for j in range(n):

                for delta in deltas:
                    dx, dy = delta
                    next_x = i + dx
                    next_y = j + dy

                    if -1 < next_x < n and -1 < next_y < n and l <= abs(
                            countrys[i][j] - countrys[next_x][next_y]) <= r:
                        tmp.add((next_x, next_y))
        
        if len(tmp) == 0:
            break

        visited = [[False for _ in range(n)] for _ in range(n)]
        # 인구 이동이 가능한 지점을 bfs로 순회
        for t in tmp:
            x, y = t
            if not visited[x][y]:
                bfs(x, y, n, l, r, countrys, visited)
        count += 1

    print(count)


if __name__ == '__main__':
    n, l, r = map(int, input().rstrip().split(' '))
    countrys = [list(map(int, input().rstrip().split(' '))) for _ in range(n)]
    main(n, l, r, countrys)
