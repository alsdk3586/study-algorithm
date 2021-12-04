# https://programmers.co.kr/learn/courses/30/lessons/84512?language=python3
count =0
found=0;

def buildVowelDictionaryNFind(depth,prevStr,word):
    global count, found
    vowels = [' ', 'A','E','I','O','U']
    
    # startIdx = endIdx = 1 
    # if depth!=1 :                           startIdx = 0
    # if depth==1 or prevStr[-1]!=' ' :        endIdx = len(vowels)
        
    # for i in range(startIdx,endIdx):
    #     v = vowels[i]
        
    #     if(depth<5):
    #         buildVowelDictionaryNFind(depth+1,prevStr+v,word)
    #     else:
    #         if(word!=prevStr+v):             count=count+1
    #         else:                            found=count+1
                        
    #     if(found):                           break;
        
    for v in vowels:
        #첫문자는 빈칸이면 안됨
        if(prevStr=="" and v==' '):                         continue
        #앞문자가 빈칸이면 빈칸만 가능
        elif(prevStr!="" and prevStr[-1]==' ' and v!=' '):  continue;
        
        if(depth<5):
            buildVowelDictionaryNFind(depth+1,prevStr+v,word)
        else:
            #못찾으면 카운트만 증가
            if(word!=prevStr+v):    count=count+1
            #찾으면 카운트+1 저장
            else:                   found=count+1
        
        #저장되었으면 리턴
        if(found):                  break;

def solution(word):
    #비교를 위해 뒤에 빈칸을 채워준다.
    while(len(word)<5):
        word += ' ';
    
    buildVowelDictionaryNFind(1,"", word);
    
    return found
   
   
# def solution(word):
#     vowels = [' ', 'A','E','I','O','U']
    
#     vowelDictionary = [];
#     while(len(word)<5):
#         word += ' ';
    
#     print("_"+word+"_")
#     answer = 0
#     for v1 in vowels:
#         if(v1==' '): continue;
#         for v2 in vowels:
#             for v3 in vowels:
#                 if(v2==' ' and v3!=' '): continue;
#                 for v4 in vowels:
#                     if(v3==' ' and v4!=' '): continue;
#                     for v5 in vowels:
#                         if(v4==' ' and v5!=' '): continue;
#                         answer+=1
#                         if(word == v1+v2+v3+v4+v5): 
#                             return answer;
                
    