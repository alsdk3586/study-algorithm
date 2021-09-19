def solution(weights, head2head):
    info = []
    heavierCnt = [0 for _ in range(len(weights))]
    
    for i in range(len(head2head)):
        if head2head[i].count("W"):
            for j in range(len(head2head[i])):
                if head2head[i][j] == "W":
                    if weights[i]<weights[j]:
                        heavierCnt[i]+=1
    
    for i in range(len(head2head)):
        info.append((i,weights[i],0 if not (len(head2head)-head2head[i].count("N")) else head2head[i].count("W")/(len(head2head)-head2head[i].count("N")), heavierCnt[i]))
            
    info = sorted(info, key=lambda x:(x[2],x[3],x[1],-x[0]), reverse=True)
    
    return [i[0]+1 for i in info]