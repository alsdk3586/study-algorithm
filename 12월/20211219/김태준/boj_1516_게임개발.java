import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

// boj_1516_게임개발
/*
 * 문제 풀이 방법
 * - 이 문제 역시 위상정렬로 풀이가 가능하다. 작업 문제 메인로직은 같고
 *   인풋, 아웃풋 형식만 조금다르다.
 *   작업 문제를 풀었다면 충분히 풀 수 있는 문제이다.
 *
 *
 */
public class Main {

	static int n;
	static int in[];
	static int buildTimeArr[];
	static int totalBuildTimeArr[];
	static Map<Integer, List<Integer>> edgeMap = new HashMap<>();
	static Queue<Integer> q = new LinkedList<>();
	
	public static void main(String args[ ]) {
		processInputData();
		topologicalSort();
		printRes( );
	}
	
	public static void processInputData() {
		Scanner scanner = new Scanner(System.in);
		n = scanner.nextInt();
	
		in = new int[n + 1];
		buildTimeArr = new int[n + 1];
		totalBuildTimeArr = new int[n + 1];
		Arrays.fill(in, 0);
		Arrays.fill(buildTimeArr, 0);
		Arrays.fill(totalBuildTimeArr, 0);
		
		for(int i=1; i<=n; i++) {
			int buildTime = scanner.nextInt();
			buildTimeArr[i] = buildTime;
			totalBuildTimeArr[i] = buildTimeArr[i];
		
			while(true) {
				int building = scanner.nextInt();
				if(building == -1) break;
				
				List<Integer> buildingList = edgeMap.get(building);
				
				if(buildingList == null) {
					buildingList = new ArrayList<>();
				}
				
				in[i]++;
				buildingList.add(i);
				edgeMap.put(building, buildingList);
			}
		}
		
	
		for(int i=1; i<=n; i++) {
			if(in[i] == 0) q.add(i);
		}
	}
	
	public static void topologicalSort( ) {
		
		while(!q.isEmpty()) {
			
			int top = q.poll();
			List<Integer> buildingList = edgeMap.get(top);
			
			if(buildingList != null) {
				for(int i=0; i<buildingList.size(); i++) {
					int building = buildingList.get(i);
					
					in[building]--;
					totalBuildTimeArr[building] = Math.max(totalBuildTimeArr[top] + buildTimeArr[building], totalBuildTimeArr[building]);
					if(in[building] == 0) q.add(building);
				}
			}
		}
	}
	
	
	public static void printRes( ) {
		StringBuilder resSb = new StringBuilder();
		
		for(int i=1; i<=n; i++) {
			resSb.append(totalBuildTimeArr[i] + "\n");
		}
		
		System.out.println(resSb.toString());
	}
}
