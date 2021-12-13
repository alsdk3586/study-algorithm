import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
	
	static int sudocu[][];
	static final int mapSize = 9;
	static List<Point> blankPointList = new ArrayList<>();
	
	public static void main(String args[ ]) {
	
		processInputData( );
		findBlackPoint();
		makeSudoCu(0);
	}
	
	public static void processInputData( ) {
		Scanner in=new Scanner(System.in);
		sudocu = new int[mapSize][mapSize];

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				sudocu[i][j] = in.nextInt();
			}
		}
		in.close();
	}
	
	public static void findBlackPoint( ) {
		for(int i=0; i<mapSize; i++) {
			for(int j=0; j<mapSize; j++) {
				if(sudocu[i][j] == 0) blankPointList.add(new Point(i, j));
			}
		}
	}
	
	public static void makeSudoCu(int d) {
		
		if(d == blankPointList.size()) {
			printRes( );
			System.exit(0);
		}
		
		Point p = blankPointList.get(d);
		int xp = p.x;
		int yp = p.y;
			
		for(int j=1; j<10; j++) {
			if(isValidPosition(xp, yp, j)) {
				sudocu[xp][yp] = j;
				makeSudoCu(d+1);
				sudocu[xp][yp] = 0;
			}
		}	
	}
	
	public static boolean isValidPosition(int xp, int yp, int v) {
	
		// 가로, 세로
		for(int i=0; i<mapSize; i++) {
			if(sudocu[xp][i] == v) return false;
			if(sudocu[i][yp] == v) return false;
		}
		
		// 3*3 사각형
		int xBlock = xp / 3;
		int yBlock = yp / 3;
		
		int startXpInBlock = xBlock*3;
		int startYpInBlock = yBlock*3;
		
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				if(sudocu[startXpInBlock + i][startYpInBlock + j] == v) return false;
			}
		}
		
		return true;
	}
	
	
	public static void printRes( ) {
		for(int i=0; i<mapSize; i++) {
			for(int j=0; j<mapSize; j++) {
				System.out.print(sudocu[i][j] + " ");
			}
			System.out.println("");
		}
	}
	
	static class Point {
		int x;
		int y;
		
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
}

