import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

// boj_2056_작업
/* 문제 풀이방법
 * - 위상정렬로 풀 수있고 선수과목 문제와 풀이는 비슷하다.
 *   차이점은 선수과목은 각 과목들의 최소 학기를 구하는 것이고, 이 문제는 전체 작업완료의 최소시간을 구하면 된다.
 *   이 문제 역시 최소시간을 구하는 것이 문제의 핵심인데
 *   선수과목처럼 나로 들어올 수 있는 작업 시간중 최대값을 구하면된다.
 *
 *   문제는 각 작업의 최소시간이 아니라 문제에 주어진 전체 작업의 최소시간이다.
 *   각 작업들의 시간 중 최대값을 구하면 답이된다. -> 영향이 없는 작업들을 동시에 실행이 가능하므로(문제의 조건) 가장 오래걸리는 작업이 끝나면 다른 작업들은 모두
 *   끝난 상태일 것이다.
 *
 *
 */
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

