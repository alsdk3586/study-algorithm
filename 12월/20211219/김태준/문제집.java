import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

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

