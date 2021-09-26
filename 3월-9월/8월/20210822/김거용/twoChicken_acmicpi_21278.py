import sys


def getMinPathForEachBuilding(targetBuilding):
    edges = list(roads)
    edges[targetBuilding][targetBuilding] = 0
    
    #플로이드 와셜
    for k in range(vertexNum): 
        for i in range(vertexNum): 
            for j in range(vertexNum):
                edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j])
    
    return edges[targetBuilding]


#Process Input And Initialize Data
vertexNum,edgeNum = map(int, input().rstrip().split(' '))
roads = [[101 for _ in range(vertexNum)] for j in range(vertexNum)]

for _ in range(edgeNum):
    buildingFrom,buildingTo = map(int, input().rstrip().split(' '))
    roads[buildingFrom-1][buildingTo-1] = 1
    roads[buildingTo-1][buildingFrom-1] = 1

#각 빌딩에 대해 해당 빌딩과 다른빌딩들의 최소 거리를 구한다.
distances = [];

for targetBuilding in range(vertexNum):
    minDistToTargetBuilding = getMinPathForEachBuilding(targetBuilding)
    distances.append( minDistToTargetBuilding )
    #print(minDistToTargetBuilding);

#두개의 빌딩을 선정해서 최단거리들의 합을 구한다음 최소거리인지 확인하고 업데이트 한다.
minDistance = sys.maxsize
combination = [];

for i in range(vertexNum):
    for j in range(i+1, vertexNum):
        tempMinDistance = 0;
        for x in range(vertexNum):
            #print(str(i) + " " + str(j) + " " + str(x))
            tempMinDistance += min(distances[i][x], distances[j][x])
        if tempMinDistance < minDistance:
            minDistance = tempMinDistance;
            combination = [i+1,j+1, minDistance*2]

#print(str(combination[0]) + " " + str(combination[1]) + " " + str(combination[2]))
#print(combination)
print(" ".join([str(x) for x in combination]))
#print("\n".join(map(str,answer)))