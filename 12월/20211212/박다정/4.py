import collections

def dfs(airports, total):
    stack = ['ICN']
    result = []
    
    while len(stack) > 0:
        current = stack[-1]
        if current not in airports or len(airports[current]) == 0:
            result.append(stack.pop())
        else:
            stack.append(airports[current].popleft())
    result.reverse()
    return result

def solution(tickets):
    answer = []
    airports = {}
    count = len(tickets)
    
    for ticket in tickets:
        start, end = ticket
        
        if start not in airports:
            airports[start] = [end]
        else:
            airports[start].append(end)

    for k, v in airports.items():
        v.sort()
        airports[k] = collections.deque(v)

    answer = dfs(airports, count)
    
    return answer