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
	static int minSemesterArr[ ];
	static Map<Integer, List<Integer>> edgeMap = new HashMap<>();
	static Queue<Integer> q = new LinkedList<>();
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
		minSemesterArr = new int[n + 1];
		Arrays.fill(in, 0);
		Arrays.fill(minSemesterArr, 0);
		
		int s1, s2;
		for(int i=0; i<m; i++) {
			s1 = scanner.nextInt();
			s2 = scanner.nextInt();
			
			List<Integer> subjectList = edgeMap.get(s1);
			
			if(subjectList == null) {
				subjectList = new ArrayList<>();
			}
			
			in[s2]++;
			subjectList.add(s2);
			edgeMap.put(s1, subjectList);
		}
		
	
		for(int i=1; i<=n; i++) {
			if(in[i] == 0) {
				q.add(i);
				minSemesterArr[i] = 1;
			}
		}
	}
	
	public static void topologicalSort() {

		while(!q.isEmpty()) {

			int top = q.poll();
			int semester = minSemesterArr[top]; 
			List<Integer> subjectList = edgeMap.get(top);
			
			if(subjectList != null) {
				for(int i=0; i<subjectList.size(); i++) {
					int subject = subjectList.get(i);
					in[subject]--;
										
					if(in[subject] == 0) {
						q.add(subject);
						minSemesterArr[subject] = Math.max(minSemesterArr[subject], semester+1);
					}
				}
			}
		}
	}
	
	public static void printRes( ) {
		StringBuilder resSb = new StringBuilder();
		for(int i=1; i<=n; i++) {
			resSb.append(minSemesterArr[i] + " ");
		}
		
		System.out.println(resSb.toString());	
	}	
}

