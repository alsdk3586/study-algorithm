import java.util.Arrays;
import java.util.Scanner;

// boj_14888_연산자끼워넣기
// 문제 설명
// - 문제에서 답을 계산할때 사칙연산의 우선순위를 생각하지 않고 무조건 앞에서부터 계산하면 된다.
// 예를들어 1÷2+3+4-5×6를 사칙연산의 우선순위를 생각한다면 -23이지만 문제에서는 앞에서부터 연산하면 되므로 12가된다.
//
/* 문제풀이방법
 - 완전탐색으로 모든 경우를 다 계산해본다.
 -> 예제 케이스 3번을 예로들어 설명하면
 + - 2개
 - - 1개
 * - 1개
 / - 1개
 의 연산자가 존재하고
 연산해야되는 값들은 1 2 3 4 5 6 이다.

 그럼 위의 연산자의 모든 케이스를 순열로 만들어서 연산해야되는 값들 사이에 넣어서 모든 경우의 값을 구해 최대/최소 값을 구할 수 있다.

  ++-* / -> 1+2+3-4*5/6
  ++-/*  -> 1+2+3-4/5*6
  ++*-/  -> 1+2+3*4-5/6
  ......

*/





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
	
	// 연산자의 모든 순열을 구한다.
	public static void dfs(int d, StringBuilder sb) {
		
		if(d == n - 1) { // 연산자 순열 바탕으로 값을 구한다.
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

