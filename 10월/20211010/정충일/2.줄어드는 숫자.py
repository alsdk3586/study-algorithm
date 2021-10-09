import sys

input = sys.stdin.readline

N = int(input())
count = [0,1,2,3,4,5,6,7,8,9]
# i=10
# while True:
#     flag = True
#     for j in range(0,len(str(i))-1):
#         if str(i)[j]<=str(i)[j+1]:
#             flag = False
#             break
#     if flag:
#         count.append(i)
#     if len(count) < int(N):
#         i+=1
#     else:
#         break

# print(count[int(N)-1])

result_idx = 0
result = 0

while len(count) != 0:
    pop_num = count.pop(0)
    result_idx += 1
    result = pop_num
    
    if result_idx == N:
        break
    
    for r in range(0, pop_num % 10):
        count.append(10 * pop_num + r)
    
if result_idx < N:
    print(-1)

elif result_idx == N:
    print(result)