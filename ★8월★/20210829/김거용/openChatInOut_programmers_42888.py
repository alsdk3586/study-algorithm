import sys

def solution(record):
    answerUID = []
    answer = []
    typeString = {"Enter":"들어왔습니다.", "Leave":"나갔습니다."}
    nicknameRecord = {}
    
    for data in record:
        splittedData = data.split(' ')
        if(splittedData[0]!="Change"):
            answerUID.append(splittedData[1])
            answer.append("님이 " + typeString[splittedData[0]])
        if(splittedData[0]!="Leave"):
            nicknameRecord[splittedData[1]] = splittedData[2]
            
    for i in range(len(answerUID)):
        answer[i] = nicknameRecord[answerUID[i]]+ answer[i]
    
    return answer