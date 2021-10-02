from collections import deque, defaultdict

def solution(priorities, location):
    N = len(priorities)
    priorities = [(idx, val) for idx, val in enumerate(priorities)]
    answer = {}
    order = 1
    while order <= N:
        max_pr = max(priorities, key=lambda x : x[1])
        pr = priorities.pop(0)
        if pr[1] == max_pr[1]:
            answer[pr[0]] = order
            order += 1
        else:
            priorities.append(pr)

    return answer[location]
