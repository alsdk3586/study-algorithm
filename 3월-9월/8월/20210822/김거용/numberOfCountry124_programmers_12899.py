import sys

def convert(n):
    T = "124"
    
    #0이 없고 1부터 시작하므로 1이 들어가면 0처럼 표기
    q, r = divmod(n-1, 3)
    if q == 0:
        return T[r]
    else:
        return convert(q) + T[r]
    
def solution(n):
    ternaryString = convert(n) 
    return ternaryString