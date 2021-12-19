import sys
import collections

input = sys.stdin.readline

def topological_sort(n, heights, nodes):
    result = collections.deque([])
    stack = []

    for i in range(1, len(nodes)):
        if nodes[i] == 0:
            stack.append(i)
    
    while stack:

        current = stack.pop()
        result.appendleft(current)
        
        for height in heights[current]:
            nodes[height] -= 1
            
            if nodes[height] == 0:
                stack.append(height)

    return result

def main(n, m, heights, nodes):
    result = topological_sort(n, heights, nodes)
    print(' '.join(map(str, result)))

if __name__ == '__main__':
    n, m = map(int, input().rstrip().split(' '))
    heights = [[] for _ in range(n+1)]
    nodes = [0 for _ in range(n+1)]
    
    for _ in range(m):
        front, back = map(int, input().rstrip().split(' '))
        heights[back].append(front)
        nodes[front] += 1

    main(n, m, heights, nodes)