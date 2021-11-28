def isLetter(char):
    if ord(char) > 64 and ord(char) < 91:
        return True
    return False

def makeMultiSet(string):
    result = []
    for i in range(len(string)-1):
        if isLetter(string[i]) and isLetter(string[i+1]):
            result.append(string[i] + string[i+1])
    return result


def getUnionCount(str1, str2):
    for i in range(len(str1)):
        for j in range(len(str2)):
            if str1[i] == str2[j]:
                str2[j] = ''
                break
    for s in str2:
        if s != '':
            str1.append(s)
    return len(str1)
    
def getInteractionCount(str1, str2):
    currentIndex = 0
    count = 0
    
    for i in range(len(str1)):
        for j in range(len(str2)):
            if str1[i] == str2[j]:
                str2[j] = ''
                count += 1
                break
    return count

def solution(str1, str2):
    str1 = str1.upper()
    str2 = str2.upper()
    
    if str1 == str2:
        return 65536
    
    str1 = makeMultiSet(str1)
    str2 = makeMultiSet(str2)
    
    interaction = getInteractionCount(str1[:], str2[:])
    union = getUnionCount(str1, str2)
    
    return int((interaction / union) * 65536)