import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    static boolean[][][][] visit; // 길 정보 저장
    static boolean[][] check; // 방문 체크
    static int n;  // 맵 크기
    static int k;  // 소 마리 수
    static int r;  // 길 정보
    static int result; // 결과
    static int[][] dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // bfs
    static Point[] p; //
    static Queue<Point> q = new LinkedList<>();
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        r = Integer.parseInt(st.nextToken());
        visit = new boolean[n + 1][n + 1][n + 1][n + 1];

        // (x1,y1) -> (x2,y2) 길 정보 입력
        for (int i = 0; i < r; i++) {
            st = new StringTokenizer(br.readLine());
            int x1 = Integer.parseInt(st.nextToken());
            int y1 = Integer.parseInt(st.nextToken());
            int x2 = Integer.parseInt(st.nextToken());
            int y2 = Integer.parseInt(st.nextToken());
            visit[x1][y1][x2][y2] = true;
            visit[x2][y2][x1][y1] = true;
        }

        // (x,y)
        p = new Point[k];

        // 전체 소 위치 저장
        for (int i = 0; i < k; i++) {
            st = new StringTokenizer(br.readLine());
            p[i] = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }

        // 가장 맨 앞에 있는 소 부터 bfs 탐색 시작
        for (int i = 0; i < k; i++) {
            check = new boolean[n + 1][n + 1]; // 방문 체크 배열 초기화
            bfs(p[i].x, p[i].y);
            // 해당 소가 그 다음 소들을 만났는지 체크
            for (int j = i + 1; j < k; j++) {

                if (!check[p[j].x][p[j].y]) { // 길을 이용한 경우 카운트 추카
                    result++;
                }
            }
        }
        System.out.println(result);

    }

    private static void bfs(int x, int y) {

        q.add(new Point(x, y));
        check[x][y] = true;
        while (!q.isEmpty()) {
            Point next = q.remove();
            for (int i = 0; i < 4; i++) {
                int x1 = next.x + dir[i][0];
                int y1 = next.y + dir[i][1];

                // map 범위 체크
                if (x1 <= 0 || x1 > n || y1 <= 0 || y1 > n)
                    continue;

                // 길을 이용 했거나, 방문 했는지 체크
                if (visit[next.x][next.y][x1][y1] || check[x1][y1])
                    continue;
                check[x1][y1] = true;
                q.add(new Point(x1, y1));
            }
        }
    }
}