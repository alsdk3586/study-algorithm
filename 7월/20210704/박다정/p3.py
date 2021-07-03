import collections


def bfs(f, s, u, d, table):
    visited = [False for _ in range(f + 1)]
    queue = collections.deque([s])
    visited[s] = True

    while queue:
        current = queue.popleft()

        if current + u < f + 1:
            next_floor = current + u

            if not visited[next_floor]:
                visited[next_floor] = True
                table[next_floor] = table[current] + 1
                queue.append(next_floor)
            else:
                table[next_floor] = min(table[current] + 1, table[next_floor])
        if current - d > 0:
            next_floor = current - d

            if not visited[next_floor]:
                visited[next_floor] = True
                table[next_floor] = table[current] + 1
                queue.append(next_floor)
            else:
                table[next_floor] = min(table[current] + 1, table[next_floor])


def main(f, s, g, u, d):
    table = [0 for _ in range(f + 1)]

    bfs(f, s, u, d, table)

    if s == g:
        print(table[s])
    elif not table[g]:
        print('use the stairs')
    else:
        print(table[g])


if __name__ == '__main__':
    f, s, g, u, d = map(int, input().split(' '))
    main(f, s, g, u, d)