import java.util.LinkedList;
import java.util.Queue;
import java.util.Arrays;

class Solution {
    public static boolean[] visited;
    public static int[][] network;
    
    private static int bfs(int x) {
        Queue<Integer> queue = new LinkedList();
        int count = 1;
        int start = x;
        visited[x] = true;
        queue.offer(start);
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
                
            for (int i = 0; i < visited.length; i += 1) {
                if (!visited[i] && network[current][i] == 1) {
                    queue.offer(i);
                    visited[i] = true;
                    count += 1;
                }
            }
        }
        return count;
    }
    
    private static void resetVisited(int n) {
        for (int i = 0; i < n; i += 1) {
            visited[i] = false;
        }
    }
    
    public int solution(int n, int[][] wires) {
        int answer = 100000000;
        network = new int[n][n];
        visited = new boolean[n];
        
        for (int[] wire : wires) {
            network[wire[0]-1][wire[1]-1] = 1;
            network[wire[1]-1][wire[0]-1] = 1;
        }
        
        // 전선 끊기
        for (int[] wire : wires) {
            network[wire[0]-1][wire[1]-1] = 0;
            network[wire[1]-1][wire[0]-1] = 0;
            int result = 0;
            
            for (int i = 0; i < n; i += 1) {
                if (!visited[i]) {
                    result = Math.abs(result - bfs(i));
                }
            }
            network[wire[0]-1][wire[1]-1] = 1;
            network[wire[1]-1][wire[0]-1] = 1;
            answer = Math.min(result, answer);
            resetVisited(n);
        }
        return answer;
    }
}
