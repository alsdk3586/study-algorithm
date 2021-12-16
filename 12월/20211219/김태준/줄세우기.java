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
	static Map<Integer, List<Integer>> edgeMap = new HashMap<>();
	static Queue<Integer> q = new LinkedList<>();
	static List<Integer> resList = new ArrayList<>();
	
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
		
		int s1, s2;
		for(int i=0; i<m; i++) {
			s1 = scanner.nextInt();
			s2 = scanner.nextInt();
			
			List<Integer> studentList = edgeMap.get(s1);
			
			if(studentList == null) {
				studentList = new ArrayList<>();
			}
			
			in[s2]++;
			studentList.add(s2);
			edgeMap.put(s1, studentList);
		}
		
		for(int i=1; i<=n; i++) {
			if(in[i] == 0) q.add(i);
		}
	}
	
	public static void topologicalSort( ) {
	
		while(!q.isEmpty()) {
			
			int top = q.poll();
			resList.add(top);
			List<Integer> studentList = edgeMap.get(top);
			
			if(studentList != null) {
				for(int i=0; i<studentList.size(); i++) {
					int s = studentList.get(i);
					in[s]--;
					if(in[s] == 0) q.add(s);
				}
			}
		}
	}
	
	public static void printRes( ) {
		for(int i=0; i<resList.size(); i++) {
			System.out.print(resList.get(i) + " ");
		}
	}
	
}

