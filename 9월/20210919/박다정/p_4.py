import sys

input = sys.stdin.readline

n, m, k = map(int, input().rstrip().split(' '))
tech_tree = [[] for _ in range(n + 1)]
is_completed = [0 for _ in range(n + 1)]
BUILD = 1
DESTROY = 2

for _ in range(m):
    parent, child = map(int, input().rstrip().split(' '))
    tech_tree[child].append(parent)


def can_builted_in(building):
    for parent in tech_tree[building]:
        if is_completed[parent] <= 0:
            return False
    return True


for _ in range(k):
    action, building = map(int, input().rstrip().split(' '))

    if action == BUILD:
        if can_builted_in(building):
            is_completed[building] += 1
            continue
        print('Lier!')
        exit(0)
    elif action == DESTROY:
        if not is_completed[building]:
            print('Lier!')
            exit(0)
        is_completed[building] -= 1

print('King-God-Emperor')
