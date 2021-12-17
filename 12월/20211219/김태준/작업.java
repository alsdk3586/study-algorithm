import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

public class Main {

	static int n;
	static int m;
	static int in[];
	static int workTimeArr[];
	static int totalWorkTimeArr[];
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
		workTimeArr = new int[n + 1];
		totalWorkTimeArr = new int[n + 1];
		Arrays.fill(in, 0);
		Arrays.fill(workTimeArr, 0);
		Arrays.fill(totalWorkTimeArr, 0);
		
		for(int i=1; i<=n; i++) {
			int workTime = scanner.nextInt();
			workTimeArr[i] = workTime;
			totalWorkTimeArr[i] = workTimeArr[i];
		
			m = scanner.nextInt();	
			for(int j=0; j<m; j++) {
				
				int work = scanner.nextInt();
				List<Integer> workList = edgeMap.get(work);
				
				if(workList == null) {
					workList = new ArrayList<>();
				}
				
				in[i]++;
				workList.add(i);
				edgeMap.put(work, workList);
			}
		}
		
	
		for(int i=1; i<=n; i++) {
			if(in[i] == 0) q.add(i);
		}
	}
	
	
	public static void topologicalSort( ) {
		
		while(!q.isEmpty()) {
			
			int top = q.poll();
			List<Integer> workList = edgeMap.get(top);
			
			if(workList != null) {
				for(int i=0; i<workList.size(); i++) {
					int work = workList.get(i);
					
					in[work]--;
					totalWorkTimeArr[work] = Math.max(totalWorkTimeArr[top] + workTimeArr[work], totalWorkTimeArr[work]);
					if(in[work] == 0) q.add(work);
				}
			}
		}
	}
	
	
	public static void printRes( ) {
		int res = -1;
		for(int i=1; i<=n; i++) {
			res = Math.max(res,  totalWorkTimeArr[i]);
		}
		
		System.out.println(res);
	}
	
}

