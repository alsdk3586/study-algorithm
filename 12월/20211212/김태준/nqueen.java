import java.util.Arrays;
import java.util.Scanner;

import java.util.Arrays;
import java.util.Scanner;

public class Main {
 
	// n by n 체크판에 n개의 퀸을 놀려면 각 줄에 1개씩 놔야함
	static int n;
	static int chessBoard[ ][ ];
	static int res = 0;
	
	
	public static void main(String args[ ]) {
		
		Scanner scanner = new Scanner(System.in);
		n = scanner.nextInt();
	
		chessBoard = new int[n][n];
		for(int i=0; i<n; i++) {
			Arrays.fill(chessBoard[i], 0);
		}
	
		dfs(0);
		System.out.println(res);
	};
	
	static void dfs(int d) {
		
		if(d == n) {
			res++;
			return;
		}
		
		for(int i=0; i<n; i++) {
			if(chessBoard[d][i] == 0) {
				fillChessBoard(d, i, 1);
				dfs(d + 1);
				fillChessBoard(d, i, -1);
			}
		}		
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

