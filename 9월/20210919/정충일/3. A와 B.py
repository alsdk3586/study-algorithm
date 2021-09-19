S = input()
T = input()

flag = False

while len(S) <= len(T):
    if S != T:
        # 뒤에 A 삭제
        if T[-1] == 'A':
            T = T[:-1]
        # B 삭제 후 뒤집기
        else:
            T = T[:-1]
            T = T[::-1]
    else:
        flag = True
        break

if flag:
    print(1)
else:
    print(0)