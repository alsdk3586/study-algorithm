import sys 

data = []
for _ in range(9):
    data += list(map(int, sys.stdin.readline().split()))

ar1= [0, 1, 2, 9, 10, 11, 18, 19, 20]
ar2= [3, 4, 5, 12, 13, 14, 21, 22, 23]
ar3= [6, 7, 8, 15, 16, 17, 24, 25, 26]
ar4= [27, 28, 29, 36, 37, 38, 45, 46, 47]
ar5= [30, 31, 32, 39, 40, 41, 48, 49, 50]
ar6= [33, 34, 35, 42, 43, 44, 51, 52, 53]
ar7= [54, 55, 56, 63, 64, 65, 72, 73, 74]
ar8= [57, 58, 59, 66, 67, 68, 75, 76, 77]
ar9= [60, 61, 62, 69, 70, 71, 78, 79, 80]
# for i in range(0, 3):
#     for j in range(0, 3):
#         ar1.append(i*9 + j)
#         ar2.append(i*9 + j+3)
#         ar3.append(i*9 + j+6)
#         ar4.append(i*9 + j+27)
#         ar5.append(i*9 + j+30)
#         ar6.append(i*9 + j+33)
#         ar7.append(i*9 + j+54)
#         ar8.append(i*9 + j+57)
#         ar9.append(i*9 + j+60)
# print(ar1)
# print(ar2)
# print(ar3)
# print(ar4)
# print(ar5)
# print(ar6)
# print(ar7)
# print(ar8)
# print(ar9)

def check(x, i):
    for a in range(0, 9):
        if data[x%9+9*a] == i or data[(x//9)*9+a] == i:
            return False
    if x in ar1:
        for el in ar1:
            if data[el] == i:
                return False
    if x in ar2:
        for el in ar2:
            if data[el] == i:
                return False
    if x in ar3:
        for el in ar3:
            if data[el] == i:
                return False
    if x in ar4:
        for el in ar4:
            if data[el] == i:
                return False
    if x in ar5:
        for el in ar5:
            if data[el] == i:
                return False
    if x in ar6:
        for el in ar6:
            if data[el] == i:
                return False
    if x in ar7:
        for el in ar7:
            if data[el] == i:
                return False
    if x in ar8:
        for el in ar8:
            if data[el] == i:
                return False
    if x in ar9:
        for el in ar9:
            if data[el] == i:
                return False
    return True


end = False
def sdc(x):
    global end
    if x == 81:
        end = True
        for i in range(9):
            for j in range(9):
                print(data[i*9 + j], end=' ')
            print()
            
    else:
        if data[x]:
            sdc(x+1)
        else:
            for i in range(1, 10):
                if check(x, i):
                    data[x] = i 
                    sdc(x+1)
                    if end:
                        return
                    data[x] = 0
            



sdc(0)