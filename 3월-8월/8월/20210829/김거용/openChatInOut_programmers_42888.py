import sys

def solution(record):
    answerUID = []
    answer = []
    typeString = {"Enter":"들어왔습니다.", "Leave":"나갔습니다."}
    nicknameRecord = {}
    
    for data in record:
        splittedData = data.split(' ')
        #입장/퇴장 순서에 맞춰 UID와 행동 기술문장을
        #한문장에 저장해두면 String Replace를 해야하므로  별도로 저장한다
        if(splittedData[0]!="Change"):
            answerUID.append(splittedData[1])
            answer.append("님이 " + typeString[splittedData[0]])
        
        #Leave는 닉네임이 없다.
        if(splittedData[0]!="Leave"):
            nicknameRecord[splittedData[1]] = splittedData[2]
    
    #최종 UID/Nickname 쌍을 이용해서 닉네임+행동기술을 합쳐 최종 문장을 완성한다.
    for i in range(len(answerUID)):
        answer[i] = nicknameRecord[answerUID[i]]+ answer[i]
    
    return answer