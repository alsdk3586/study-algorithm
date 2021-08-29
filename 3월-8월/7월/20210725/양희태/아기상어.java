import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    static int[][] dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; // 상하 좌우 이동
    static int N; // 공간 크기
    static int[][] map; // 공간
    static boolean[][] visited; // 방문 체크
    static int size = 2; // 아기 상어 최초 크기
    static int eat = 0; // 아기 상어 물고기 먹은 개수
    static int move = 0; // 이동 거리

    // 아기 상어 정보
    static class Info {
        int x; // x
        int y; // y
        int dist; // 거리

        public Info(int x, int y, int dist) {
            this.x = x;
            this.y = y;
            this.dist = dist;
        }
    }

    // 먹이 정보 (거리 -> 가장 위 -> 가장 왼쪽 순서로 비교) -1(왼), 1(오)
    static Queue<Info> pq = new PriorityQueue<>((o1, o2) -> o1.dist != o2.dist ? Integer.compare(o1.dist, o2.dist) :
            (o1.x != o2.x ? Integer.compare(o1.x, o2.x) : Integer.compare(o1.y, o2.y)));

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken()); //공간 크기 입력
        map = new int[N][N]; // map 배열 생성
        visited = new boolean[N][N]; // 방문 체크

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < N; j++) {
                map[i][j] = Integer.parseInt(st.nextToken()); // map 배열 값
                if (map[i][j] == 9) {
                    visited[i][j] = true; // 방문 체크
                    map[i][j] = 0;
                    pq.add(new Info(i, j, 0)); // 상어 처음 위치 큐에 삽입
                }
            }
        }
        move(); // 아기 상어 이동
    }

    private static void move() {

        while (!pq.isEmpty()) {
            Info shark = pq.poll(); // 상어 정보 꺼내기

            // bfs
            for (int i = 0; i < 4; i++) {
                int dx = shark.x + dir[i][0];
                int dy = shark.y + dir[i][1];

                if (!(dx >= 0 && dy >= 0 && dx < N && dy < N)) continue;
                if (visited[dx][dy]) continue;
                visited[dx][dy] = true;

                if (map[dx][dy] <= size) {
                    pq.add(new Info(dx, dy, shark.dist + 1));
                }
            }

            if (pq.peek() != null) {
                Info info = pq.peek(); // queue 맨 앞 정보 확인

                // 물고기 먹는 로직
                if (map[info.x][info.y] < size && map[info.x][info.y] > 0) {
                    eat++; // 물고기 먹은 수 증가

                    if (size == eat) { // 상어 사이즈 랑 먹은 물고기 수가 같은 경우 사이즈 크기 증가
                        size++;
                        eat = 0;
                    }
                    map[info.x][info.y] = 0; // 물고기 먹은 위치 0으로 변경

                    pq.clear(); // 큐 비우기
                    pq.add(new Info(info.x, info.y, 0));
                    move += info.dist;
                    visited = new boolean[N][N];
                    visited[info.x][info.y] = true;
                }
            }
        }
        System.out.println(move);
    }
}
