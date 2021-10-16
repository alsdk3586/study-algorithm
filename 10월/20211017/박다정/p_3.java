import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;

public class b_2580 {
    private static final int[][] board = new int[9][9];
    private static final ArrayList<int[]> list = new ArrayList<>();

    private static boolean isDuplicated(int x, int y, int number) {
        for (int i = 0; i < 9; i += 1) {
            if (board[x][i] == number) {
                return true;
            }
            if (board[i][y] == number) {
                return true;
            }
        }

        int row = (x / 3) * 3;
        int column = (y / 3) * 3;

        for (int i = row; i < row + 3 ; i += 1) {
            for (int j = column; j < column + 3; j += 1) {
                if (board[i][j] == number) {
                    return true;
                }
            }
        }
        return false;
    }


    private static void printAnswer() {
        for (int[] row : board) {
            System.out.println(Arrays.toString(row).replaceAll("[^0-9 ]", ""));
        }
        System.exit(0);
    }

    private static void dfs(int current) {

        if (list.size() == current) {
            printAnswer();
            System.exit(0);
        }

        int[] location = list.get(current);
        int x = location[0];
        int y = location[1];

        for (int j = 1; j < 10; j += 1) {
            if (!isDuplicated(x, y, j)) {
                board[x][y] = j;
                dfs(current + 1);
                board[x][y] = 0;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for (int i = 0; i < 9; i += 1) {
            String[] row = br.readLine().split(" ");
            for (int j = 0; j < 9; j += 1) {
                board[i][j] = Integer.parseInt(row[j]);

                if (board[i][j] == 0) {
                    int[] location = {i, j};
                    list.add(location);
                }
            }
        }
        dfs(0);
    }
}
