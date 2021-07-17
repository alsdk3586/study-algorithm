import sys
import collections

input = sys.stdin.readline
INF = sys.maxsize
n, m = map(int, input().rstrip().split(' '))
board = [list(map(int, list(input().rstrip()))) for _ in range(n)]
visited = [[[INF] * m for _ in range(n)] for _ in range(2)]
deltas = [(0, -1), (0, 1), (-1, 0), (1, 0)]


# https://backtony.github.io/algorithm/2021/02/16/algorithm-boj-class4-16/

def bfs(i, j, n, m):
    visited[0][i][j] = 1
    queue = collections.deque([[0, i, j]])

    while queue:
        status, x, y = queue.popleft()

        for delta in deltas:
            dx, dy = delta
            next_x = x + dx
            next_y = y + dy

            if -1 < next_x < n and -1 < next_y < m:
                # 다음 이동 칸에 벽이 없고 방문하지 않았을 때
                if board[next_x][next_y] == 0 and visited[status][next_x][next_y] == INF:
                    visited[status][next_x][next_y] = visited[status][x][y] + 1
                    queue.append([status, next_x, next_y])
                # 다음 이동 칸에 벽이 있고 방문하지 않았으며 벽을 부순적이 없을 때
                elif board[next_x][next_y] == 1 and visited[1][next_x][next_y] == INF and status == 0:
                    visited[1][next_x][next_y] = visited[status][x][y] + 1
                    queue.append([1, next_x, next_y])

    return min(visited[0][n - 1][m - 1], visited[1][n - 1][m - 1])


def main():
    result = bfs(0, 0, len(board), len(board[0]))

    if result == INF:
        print(-1)
    else:
        print(result)


if __name__ == '__main__':
    main()
