def getDistanceFromChar(inputNum, targetNumber):
    numberCoord = {
        1:[0,0],        2:[0,1],        3:[0,2],
        4:[1,0],        5:[1,1],        6:[1,2],
        7:[2,0],        8:[2,1],        9:[2,2],
        '*':[3,0],        0:[3,1],        '#':[3,2],
    }
    
    inputCoord = numberCoord[inputNum]
    targetCoord = numberCoord[targetNumber]
    return abs(inputCoord[0] - targetCoord[0]) + abs(inputCoord[1] - targetCoord[1]);
def checkDistanceAndPreference(hand, number, currLeftHandNum, currRightHandNum):
    usedHand = hand
    distFromLeft = getDistanceFromChar(currLeftHandNum, number)
    distFromRight = getDistanceFromChar(currRightHandNum, number)

    if(distFromLeft<distFromRight):
        usedHand = 'L'
    if(distFromLeft>distFromRight):
        usedHand = 'R'
        
    return usedHand;

def solution(numbers, hand):
    answer = ''
    
    currLeftHandNum = '*'
    currRightHandNum = '#'
    
    if(hand=='left'):
        hand='L'
    else:
        hand='R'
        
    for number in numbers:  
        if(number in [1,4, 7]):
            usedHand = 'L'
        elif(number in [3, 6, 9]):
            usedHand = 'R'
        else:
            usedHand = checkDistanceAndPreference(hand, number, currLeftHandNum, currRightHandNum)
            
        
        if(usedHand == 'L'):
            currLeftHandNum = number;
        else:
            currRightHandNum = number;
            
        answer += usedHand
        
    
    return answer