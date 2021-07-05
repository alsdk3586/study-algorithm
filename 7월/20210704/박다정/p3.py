import collections


def bfs(f, s, u, d, table):
    visited = [False for _ in range(f + 1)]
    queue = collections.deque([s])
    visited[s] = True

    while queue:
        current = queue.popleft()
        next_floors = [current + u, current - d]

        for next_floor in next_floors:
            if 0 < next_floor < f + 1 and not visited[next_floor]:
                visited[next_floor] = True
                table[next_floor] = table[current] + 1
                queue.append(next_floor)


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
