N = int(input())

solution=sorted(list(map(int, input().split())))

result = 9999999999999
start = 0
end = N-1
one = 0
two = 0

while start<end:
    temp = solution[start] + solution[end]
    zero = abs(temp)

    if result>zero:
        result=zero
        one = solution[start]
        two = solution[end]
    
    if temp>0:
        end-=1
    else:
        start+=1

print(one,two)
