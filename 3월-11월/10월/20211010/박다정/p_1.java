import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class b_17129 {
    private static int n;
    private static int m;
    private static final int[][] MOVES = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    private static char[][] board;
    private static boolean[][] visited;
    private static Queue<int[]> queue = new LinkedList();

    private static int[] getBirdLocation() {
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < m; j += 1) {
                if (board[i][j] == '2') {
                    int[] arr = new int[3];
                    arr[0] = i;
                    arr[1] = j;
                    arr[2] = 0;
                    return arr;
                }
            }
        }
        return new int[1];
    }

    private static int bfs() {
        int[] start = getBirdLocation();
        visited[start[0]][start[1]] = true;
        queue.offer(start);

        char wall = '1';
        char korea = '3';
        char japan = '4';
        char usa = '5';

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            for (int[] move : MOVES) {
                int dx = move[0], dy = move[1];
                int nextX = current[0] + dx, nextY = current[1] + dy;
                if (nextX < 0 || nextX >= n || nextY < 0 || nextY >= m ||
                        board[nextX][nextY] == wall || visited[nextX][nextY]) {
                    continue;
                }

                int[] next = new int[3];
                next[0] = nextX;
                next[1] = nextY;
                next[2] = current[2] + 1;

                if (board[nextX][nextY] == korea || board[nextX][nextY] == japan || board[nextX][nextY] == usa) {
                    return next[2];
                }
                visited[nextX][nextY] = true;
                queue.offer(next);
            }
        }
        return 0;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] s = br.readLine().split(" ");

        n = Integer.parseInt(s[0]);
        m = Integer.parseInt(s[1]);

        board = new char[n][m];
        visited = new boolean[n][m];

        for (int i = 0; i < n; i += 1) {
            String str = br.readLine();
            for (int j = 0; j < m; j += 1) {
                board[i][j] = str.charAt(j);
                visited[i][j] = false;
            }
        }

        int result = bfs();

        if (result == 0) {
            System.out.println("NIE");
        } else {
            System.out.println("TAK");
            System.out.println(result);
        }
    }
}
