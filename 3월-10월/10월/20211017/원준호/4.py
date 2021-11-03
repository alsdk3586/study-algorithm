import heapq

def solution(scoville, K):
    
    heap = []
    for scov in scoville:
        heapq.heappush(heap, scov)
    
    cnt = 0
    while len(heap) > 1:
        if heap[0] >= K:
            break
            
        x = heapq.heappop(heap)            
        y = heapq.heappop(heap)
        heapq.heappush(heap, x+y*2)
        cnt += 1
    if heap[0] >= K :
        return cnt
    else:
        return -1
