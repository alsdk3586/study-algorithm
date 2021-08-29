from collections import defaultdict
def solution(record):
    
    users = {}
    actions = []
    for idx, sent in enumerate(record):
        sent = sent.split(" ")
        
        if sent[0] == "Change":
            users[sent[1]] = sent[2]
        elif sent[0] == "Leave":
            actions.append((sent[1], "님이 나갔습니다."))
        else:
            actions.append((sent[1], "님이 들어왔습니다."))
            users[sent[1]] = sent[2]
    
    answer = []
    for id, action in actions :
        answer.append(users[id] + action)
        # print(users[id], action)
    
    return answer
    
    
