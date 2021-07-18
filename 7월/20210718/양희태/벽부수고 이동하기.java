public class Main {

    static boolean[][][] visited; //벽이 부서진 상태일때, 아닐때 따로 확인
    static int[][] arr;
    static int[][] d = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; //상하좌우
    static BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

    public static class Point {
        int x;  //위치
        int y;
        int count; //이동 횟수
        int wall; //벽 부순 여부

        Point(int x, int y, int count, int wall) {
            this.x = x;
            this.y = y;
            this.count = count;
            this.wall = wall;
        }
    }

    public static void bfs(int n, int m) {
        Queue<Point> q = new LinkedList<>();

        q.offer(new Point(0, 0, 1, 0));
        visited[0][0][0] = true;
        visited[0][0][1] = true;

        while (!q.isEmpty()) {
            Point p = q.poll();
            if (p.x == m - 1 && p.y == n - 1) {
                System.out.println(p.count);
                return;
            }

            // 상하좌우 확인
            for (int i = 0; i < 4; i++) {
                int pX = p.x + d[i][1];
                int pY = p.y + d[i][0];
                // 범위 내에 있을때
                if (pX >= 0 && pX < m && pY >= 0 && pY < n) {
                    //벽일 경우
                    if (arr[pY][pX] == 1) {
                        // 벽을 부수지 않은 상태일 경우 부순후 방문
                        if (p.wall == 0 && !visited[pY][pX][1]) {
                            q.offer(new Point(pX, pY, p.count + 1, 1));
                            visited[pY][pX][1] = true;
                        }
                    } else {
                        if (!visited[pY][pX][p.wall]) {
                            q.offer(new Point(pX, pY, p.count + 1, p.wall));
                            visited[pY][pX][p.wall] = true;
                        }
                    }
                }
            }

        }

        System.out.println(-1);
    }

    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(input.readLine());
        int n = Integer.parseInt(st.nextToken());    // 세로
        int m = Integer.parseInt(st.nextToken());   // 가로
        arr = new int[n][m];
        visited = new boolean[n][m][2];

        for (int i = 0; i < n; i++) {
            String[] temp = input.readLine().split("");
            for (int j = 0; j < temp.length; j++) {
                arr[i][j] = Integer.parseInt(temp[j]);
            }
        }
        bfs(n, m);
    }
}