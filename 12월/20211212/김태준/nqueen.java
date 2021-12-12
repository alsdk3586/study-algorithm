import java.util.*;

import java.util.Arrays;
import java.util.Scanner;

/*
 * nqueen 최적화 코드 풀이
 * - nqueen의 퀸 배치를 보면 답이되는 case가 쌍을 이루는 특징을 가지고 있다. 따라서, 1행의 n/2까지만 dfs를 탐색해서 결과에 *2를하면 
 *   1행의 탐색을 n -> n/2가 되므로 탐색시간이 줄게된다.
 *
 *   여기서 주의할 점은 n이 홀수/짝수를 구분해줘야한다.
 *
 *   짝수 : (n/2)까지 돌고 결과에 *2
 *   홀수 : 1열기준 각 행에 퀸을 놓았을때 문제의 조건을 만족하는 경우의수를 colResList로 관리한다.
 *         (n/2)+1 까지 돌고 colResList의 마지막전 요소*2 + (colResList의 마지막원소 - colResList의 마지막 전 요소)
 *         
 *   
 */
public class Main {

    // n by n 체크판에 n개의 퀸을 놀려면 각 줄에 1개씩 놔야함
    static int n;
    static int chessBoard[ ][ ];
    static List<Integer> colResList = new ArrayList<>();

    public static void main(String args[ ]) {

        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt ();

        chessBoard = new int[n][n];
        for(int i=0; i<n; i++) {
            Arrays.fill(chessBoard[i], 0);
        }

        int res = dfs(0);
        if(n%2==0) System.out.println(res*2);
        else {
            int size = colResList.size();
            if(size < 2) System.out.println(res);
            else {
                int colA = colResList.get(size - 1);
                int colB = colResList.get(size - 2);
                System.out.println(colB * 2 + (colA - colB));
            }
        }
    };

    static int dfs(int d) {

        if(d == n) return 1;

        int ret = 0;
        int idx = n;
        if(d == 0) {
            if(n%2 == 0) idx = (n/2);
            else idx = (n/2) + 1;
        }

        for(int i=0; i<idx; i++) {
            if(chessBoard[d][i] == 0) {
                fillChessBoard(d, i, 1);
                ret += dfs(d + 1);
                if(d==0) {
                    colResList.add(ret);
                }
                fillChessBoard(d, i, -1);
            }
        }

        return ret;
    }

    static void fillChessBoard(int xp, int yp, int v) {

        //세로
        for(int i=0; i<n; i++) {
            if(i==xp) continue;
            chessBoard[i][yp] += v;
        }

        // 대각선
        int xp2 = xp + 1;
        int yp2 = yp + 1;
        //우하
        while(xp2 < n && yp2 < n) {
            chessBoard[xp2][yp2] += v;
            xp2 += 1;
            yp2 += 1;
        }

        xp2 = xp + 1;
        yp2 = yp - 1;
        // 좌하
        while(xp2 < n && 0 <= yp2) {
            chessBoard[xp2][yp2] += v;
            xp2 += 1;
            yp2 -= 1;
        }
    }
}

