import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    static int F, S, G, U, D;
    static int[] dp;
    static boolean[] visited;

    private static void startLink(int now) {
        Queue<Integer> q = new LinkedList<>();

        q.offer(now);
        int time = 0;
        while (!q.isEmpty()) {
            time++;
            int size = q.size();
            while (size-- > 0) {
                int temp = q.poll();
                if (temp + U <= F && !visited[temp + U]) {
                    dp[temp + U] = time;
                    visited[temp + U] = true;
                    q.offer(temp + U);
                }
                if (temp - D >= 1 && !visited[temp - D]) {
                    dp[temp - D] = time;
                    visited[temp - D] = true;
                    q.offer(temp - D);
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        F = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken());
        G = Integer.parseInt(st.nextToken());
        U = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        dp = new int[F + 1];
        dp[S] = 0;
        visited = new boolean[F + 1];
        visited[S] = true;
        startLink(S);

        if (dp[G] == 0 && G != S) {
            System.out.println("use the stairs");
        } else {
            System.out.println(dp[G]);
        }

    }
}
