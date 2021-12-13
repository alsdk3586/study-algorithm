import java.util.Arrays;
import java.util.Scanner;

public class Main {

	//외판원 순회2
	static int n;
	static int W[][];
	static boolean visit[];
	static int res = 10000001;
	
	public static void main(String args[ ]) {
		
		processInputData( );
		goTravel( );
		System.out.println(res);
	}
	
	public static void processInputData( ) {
		
		Scanner in=new Scanner(System.in);
		n = in.nextInt();
		
		W = new int[n][n];
		visit = new boolean[n];
		
		Arrays.fill(visit, false);
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				W[i][j] = in.nextInt();
			}
		}
	}
	
	public static void goTravel( ) {
		// 출발 도시 선택 (1-n)
		for(int i=0; i<n; i++) {
			visit[i]=true;
			dfs(0, i, i, 0);
			visit[i]=false;
		}
	}
	
	public static void dfs(int d, int startCity, int nowCity, int cost) {
		
		if(d == n - 1) {
			int lastCost = W[nowCity][startCity];
			
			if(lastCost != 0) {
				res = Math.min(res,  cost + lastCost);
			}
			return;
		}
		
		for(int i=0; i<n; i++) {
			if(visit[i]) continue;
			if(W[nowCity][i] == 0) continue;
	
			visit[i] = true;
			dfs(d+1, startCity, i, cost + W[nowCity][i]);
			visit[i] = false;
		}
	}	
}

