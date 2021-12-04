import java.util.PriorityQueue;

class Solution {
    public int solution(int[] scoville, int K) {
        int answer = 0;
        PriorityQueue<Integer> pQueue = new PriorityQueue<>();
        
        for (int s : scoville) {
            pQueue.offer(s);
        }
                
        while (pQueue.peek() < K && pQueue.size() > 1) {
            
            int theMostMild = pQueue.poll();
            int theSecondMild = pQueue.poll();

            
            int newMildScovile = theMostMild + theSecondMild * 2;
            pQueue.offer(newMildScovile);
            answer += 1;
        }
        
        if (answer == 0 && pQueue.peek() == K) {
            return 0;
        }
        
        if (pQueue.peek() < K) {
            return -1;
        }
        
        return answer;
    }
}