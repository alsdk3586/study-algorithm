import sys

def solution(words):
    answer = 0
    
    sortedWords = sorted(words);
    sortedWords.append(" ");
    prevMatchScore = 0;
    for i in range(len(sortedWords)-1):
        print(sortedWords[i] + " " + sortedWords[i+1])
        
        matchScore = 0;
        for x in range(len(sortedWords[i])):
            if sortedWords[i][x] != sortedWords[i+1][x]:
                break
            matchScore+=1
                 
        #문자열 길이만큼 맞으면 해당 문자열 길이만큼 +
        if matchScore == len(sortedWords[i]):
            answer += matchScore               
        #문자열 길이이하로 맞으면 맞은 길이 +1
        elif matchScore>prevMatchScore:
            answer += matchScore+1
            #print(matchScore+1) 
        #뒷문자열과는 안비슷하지만 앞문자열과 비슷하면 이전 맞은 길이 +1
        elif prevMatchScore>matchScore:
            answer += prevMatchScore+1
            #print(prevMatchScore+1) 
        #연속해서 동일한 길이가 Match되고 뒷부분만 다르면 이전 맞은 길이 +1
        else:
            answer += prevMatchScore+1
            #print(prevMatchScore+1)
        #print(answer)
        prevMatchScore = matchScore
    
    return answer