import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class b_9663 {
    private static int[][] board;
    private static boolean[][] visited;
    private static int[] prev;

    private static boolean isComfortZone(int x, int y) {
        for (int i = 0; i < x; i++) {
            if (prev[i] == y || Math.abs(i - x) == Math.abs(prev[i] - y)) {
                return false;
            }
        }
        return true;
    }

    private static int rec(int n, int current) {
        if (current == n) {
            return 1;
        }

        int result = 0;

        for (int i = 0; i < n; i += 1) {
            if (!visited[current][i] && isComfortZone(current, i)) {
                visited[current][i] = true;
                prev[current] = i;
                result += rec(n, current + 1);
                visited[current][i] = false;
                prev[current] = 0;
            }
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        board = new int[n][n];
        visited = new boolean[n][n];
        prev = new int[n];
        System.out.println(rec(n, 0));
    }
}
