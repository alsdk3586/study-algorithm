T = int(input()) #반복횟수

for _ in range(T):
    check = 0 #초기화
    indx = 0
    s1 = input() #값 입력받기
    s2=s1 #복사본 생성

    for i in range(int(len(s1)/2)): #검사
        if(s1[i] != s1[len(s1) -i -1]):
            check = 2 #대칭이 아니면 해당 인덱스 저장, 체크 표시
            indx = i
            break
    
    if(not check): print(0) #체크가 안 되어 있다면 회문
    else:
        check = 0 #초기화
        check1 = 0
        check2 = 0
        indx2 = len(s1)-indx-1 #해당 인덱스 반대편 인덱스 위치 저장
        s1 = s1[:indx] +s1[indx+1:] #대칭이 아닌 요소 지우기
        s2 = s2[:indx2] + s2[indx2+1:]

        for i in range(int(len(s2)/2)): #검사
            if(s2[i] != s2[len(s2) -i -1]): check1=2
            if(s1[i] != s1[len(s1) -i -1]): check2=2
        if(check1+check2 == 4): check=2
        if(not check): print(1) #체크 X시 유사회문
        else: print(2) #그 외