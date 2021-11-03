import heapq

def solution(scoville, K):
    heapq.heapify(scoville)
    minCnt = 0
    while scoville[0]<K and len(scoville)>1:
        mix = heapq.heappop(scoville)+(heapq.heappop(scoville)*2)
        heapq.heappush(scoville,mix)
        minCnt+=1
    return minCnt if scoville[0]>=K else -1