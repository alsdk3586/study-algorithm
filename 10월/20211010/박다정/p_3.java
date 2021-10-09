import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class b_2234 {
    private static int n;
    private static int m;
    private static int[][] castle;
    private static final int[][][] moves = new int[16][4][2];
    private static boolean[][] visited;
    private static final List<int[]> walls = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] numbers = br.readLine().split(" ");

        n = Integer.parseInt(numbers[0]);
        m = Integer.parseInt(numbers[1]);

        castle = new int[m][n];
        visited = new boolean[m][n];

        for (int i = 0; i < m; i += 1) {
            String[] row = br.readLine().split(" ");
            for (int j = 0; j < n; j += 1) {
                castle[i][j] = Integer.parseInt(row[j]);
                visited[i][j] = false;
            }
        }

        List<Integer> roomAreas = new ArrayList<>();

        setUp();

        for (int i = 0; i < m; i += 1) {
            for (int j = 0; j < n; j += 1) {
                int currentRoomArea = 0;
                if (!visited[i][j]) {
                    currentRoomArea = bfs(i, j);
                    roomAreas.add(currentRoomArea);
                }
            }
        }
        int brokenWallArea = 0;
        for (int i = 0; i < m; i += 1) {
            for (int j = 0; j < n; j += 1) {
                for (int wall : walls.get(castle[i][j])) {
                    if (wall == 0) {
                        continue;
                    }
                    int prev = castle[i][j];
                    castle[i][j] -= wall;
                    resetVisited();
                    brokenWallArea = Math.max(brokenWallArea, bfs(i, j));
                    castle[i][j] = prev;
                }
            }
        }

        Collections.sort(roomAreas, Collections.reverseOrder());
        System.out.println(roomAreas.size());
        System.out.println(roomAreas.get(0));
        System.out.println(brokenWallArea);
    }

    private static void resetVisited() {
        for (int i = 0; i < m; i += 1) {
            for (int j = 0; j < n; j += 1) {
                visited[i][j] = false;
            }
        }
    }

    private static int bfs(int x, int y) {
        Queue<int[]> queue = new LinkedList();
        visited[x][y] = true;
        int[] start = {x, y};
        queue.offer(start);

        int roomArea = 1;

        while (!queue.isEmpty()) {
            int[] current = queue.poll();

            int currentX = current[0];
            int currentY = current[1];

            for (int[] locations : moves[castle[currentX][currentY]]) {
                for (int i = 0; i < locations.length; i += 2) {
                    if (locations[0] == 0 && locations[i + 1] == 0) {
                        break;
                    }

                    int nextX = currentX + locations[i];
                    int nextY = currentY + locations[i + 1];

                    if (-1 < nextX && nextX < m && -1 < nextY && nextY < n && !visited[nextX][nextY]) {
                        visited[nextX][nextY] = true;
                        roomArea += 1;
                        int[] next = {nextX, nextY};
                        queue.offer(next);
                    }
                }
            }
        }
        return roomArea;
    }

    private static void setUp() {
        moves[0][0][0] = -1;
        moves[0][0][1] = 0;
        moves[0][1][0] = 1;
        moves[0][1][1] = 0;
        moves[0][2][0] = 0;
        moves[0][2][1] = -1;
        moves[0][3][0] = 0;
        moves[0][3][1] = 1;
        int[] tmp0 = {0};
        walls.add(tmp0);

        moves[1][0][0] = -1;
        moves[1][0][1] = 0;
        moves[1][1][0] = 1;
        moves[1][1][1] = 0;
        moves[1][2][0] = 0;
        moves[1][2][1] = 1;
        int[] tmp1 = {1};
        walls.add(tmp1);

        moves[2][0][0] = 0;
        moves[2][0][1] = 1;
        moves[2][1][0] = 0;
        moves[2][1][1] = -1;
        moves[2][2][0] = 1;
        moves[2][2][1] = 0;
        int[] tmp2 = {2};
        walls.add(tmp2);

        moves[3][0][0] = 1;
        moves[3][0][1] = 0;
        moves[3][1][0] = 0;
        moves[3][1][1] = 1;
        int[] tmp3 = {1, 2};
        walls.add(tmp3);

        moves[4][0][0] = -1;
        moves[4][0][1] = 0;
        moves[4][1][0] = 1;
        moves[4][1][1] = 0;
        moves[4][2][0] = 0;
        moves[4][2][1] = -1;
        int[] tmp4 = {4};
        walls.add(tmp4);

        moves[5][0][0] = 1;
        moves[5][0][1] = 0;
        moves[5][1][0] = -1;
        moves[5][1][1] = 0;
        int[] tmp5 = {1, 4};
        walls.add(tmp5);

        moves[6][0][0] = 1;
        moves[6][0][1] = 0;
        moves[6][1][0] = 0;
        moves[6][1][1] = -1;
        int[] tmp6 = {2, 4};
        walls.add(tmp6);

        moves[7][0][0] = 1;
        moves[7][0][1] = 0;
        int[] tmp7 = {1,2,4};
        walls.add(tmp7);

        moves[8][0][0] = -1;
        moves[8][0][1] = 0;
        moves[8][1][0] = 0;
        moves[8][1][1] = 1;
        moves[8][2][0] = 0;
        moves[8][2][1] = -1;
        int[] tmp8 = {8};
        walls.add(tmp8);

        moves[9][0][0] = -1;
        moves[9][0][1] = 0;
        moves[9][1][0] = 0;
        moves[9][1][1] = 1;
        int[] tmp9 = {1, 8};
        walls.add(tmp9);

        moves[10][0][0] = 0;
        moves[10][0][1] = -1;
        moves[10][1][0] = 0;
        moves[10][1][1] = 1;
        int[] tmp10 = {2, 8};
        walls.add(tmp10);

        moves[11][0][0] = 0;
        moves[11][0][1] = 1;
        int[] tmp11 = {1, 2, 8};
        walls.add(tmp11);

        moves[12][0][0] = -1;
        moves[12][0][1] = 0;
        moves[12][1][0] = 0;
        moves[12][1][1] = -1;
        int[] tmp12 = {1, 2};
        walls.add(tmp12);

        moves[13][0][0] = -1;
        moves[13][0][1] = 0;
        int[] tmp13 = {1, 4, 8};
        walls.add(tmp13);

        moves[14][0][0] = 0;
        moves[14][0][1] = -1;
        int[] tmp14 = {2, 4, 8};
        walls.add(tmp14);

        int[] tmp15 = {1, 2, 4, 8};
        walls.add(tmp15);
    }
}
