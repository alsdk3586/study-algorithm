import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

// boj_1766_문제집
// 문제풀이 방법
/* 
 * - 줄세우기 문제와 완전 같은 문제인데 조건이 1개 추가됬다.
 *   "가능하면 쉬운문제 부터 풀어야한다."
 *   -> 문제의 번호가 문제의 난이도를 의미한다. 즉, 번호가 높을수록 어려운문제. 따라서, 번호가 낮은문제부터 풀어야함.
 *  
 *  우선순위 큐를 사용해서 난이도가 낮은 문제부터 뽑아서 출력한다.
 *
 *
 *
 *
 */

public class Main {

	static int n;
	static int m;
	static int in[];
	static Map<Integer, List<Integer>> edgeMap = new HashMap<>();
	static PriorityQueue<Integer> pq = new PriorityQueue<>();
	static StringBuilder resSb = new StringBuilder();
	
	public static void main(String args[ ]) {
		processInputData();
		topologicalSort();
		printRes( );
	}
	
	public static void processInputData() {
		Scanner scanner = new Scanner(System.in);
		n = scanner.nextInt();
		m = scanner.nextInt();
	
		in = new int[n + 1];
		Arrays.fill(in, 0);
		
		int q1, q2;
		for(int i=0; i<m; i++) {
			q1 = scanner.nextInt();
			q2 = scanner.nextInt();
			
			List<Integer> questionList = edgeMap.get(q1);
			
			if(questionList == null) {
				questionList = new ArrayList<>();
			}
			
			in[q2]++;
			questionList.add(q2);
			edgeMap.put(q1, questionList);
		}
		
	
		for(int i=1; i<=n; i++) {
			if(in[i] == 0) pq.add(i);
		}
	}
	
	public static void topologicalSort( ) {
	
		while(!pq.isEmpty()) {
			
			int top = pq.poll();
			resSb.append(top + " ");
			List<Integer> studentList = edgeMap.get(top);
			
			if(studentList != null) {
				for(int i=0; i<studentList.size(); i++) {
					int s = studentList.get(i);
					in[s]--;
					if(in[s] == 0) pq.add(s);
				}
			}
		}
	}
	
	public static void printRes( ) {
		System.out.println(resSb.toString());
	}
}

