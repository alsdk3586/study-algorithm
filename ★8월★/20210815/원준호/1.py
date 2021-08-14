N = int(input())

# 끝에 문자에서부터 시작해 양쪽 문자열이 같은지 비교
def check(i, j, string):
    while i < j:
        if string[i] == string[j]:
            i += 1
            j -= 1
        else:
            return i,j
    return True

answer = []
for _ in range(N):
    string = input()

    ret = check(0, len(string)-1, string)
    # 한번에 string을 다 돈다면 펠린드롬
    if ret == True:
        answer.append(0)
    else:
        i, j = ret
        # 한번 실패했을 때, 해당 문자를 제거하고 다 돌면 유사 펠린드롬
        if check(i+1, j, string) == True or check(i, j-1, string) == True:
            answer.append(1)
        else:
            answer.append(2)

for ans in answer:
    print(ans)
