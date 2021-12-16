import java.util.Arrays;
import java.util.Scanner;

public class Main {

	static int n;
	static int input[ ];
	static int operationCount[ ] = new int[4]; // +, -, *, / 연산자 갯수
	static int resMax = -1000000001;
	static int resMin = 1000000001;
	
	public static void main(String args[ ]) {
		 
		processInputData();
		dfs(0, new StringBuilder());
		printResult( );
	}
	
	public static void processInputData( ) {
		Scanner in=new Scanner(System.in);
		n = in.nextInt();
		
		input = new int[n];
		
		for(int i=0; i<n; i++) {
			input[i] = in.nextInt();
		}
		
		for(int i=0; i<4; i++) {
			operationCount[i] = in.nextInt();
		}
	}
	
	public static void dfs(int d, StringBuilder sb) {
		
		if(d == n - 1) {
			resMax = Math.max(calScore(sb), resMax);
			resMin = Math.min(calScore(sb), resMin);
			return;
		}
		
		for(int i=0; i<4; i++) {
			if(operationCount[i] == 0) continue;
			
			for(int j=0; j<operationCount[i]; j++) {
				
				if(i==0) { // +
					sb.append("+");
				} else if(i==1) { // -
					sb.append("-");
				} else if(i== 2) { // *
					sb.append("*");
				} else if(i==3) { // /
					sb.append("/");
				}
				
				operationCount[i]--;
				dfs(d+1, sb);
				operationCount[i]++;
				sb.deleteCharAt(sb.length() - 1);
			}
		}
	}
	
	public static int calScore(StringBuilder operationSb) {

		int res = input[0];
		for(int i=0; i<operationSb.length(); i++)  {
			char op = operationSb.charAt(i);
			
			if(op == '+') res += input[i+1];
			else if(op == '-') res -= input[i+1]; 
			else if(op == '*') res *= input[i+1];
			else if(op == '/') res /= input[i+1];
		}
		
		return res;
	}
	
	public static void printResult( ) {
		System.out.println(resMax);
		System.out.println(resMin);
	}
} 

