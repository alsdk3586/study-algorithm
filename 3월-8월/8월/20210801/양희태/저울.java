import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;
        StringBuilder sb = new StringBuilder();

        int n = Integer.parseInt(br.readLine());
        int m = Integer.parseInt(br.readLine());

        int[][] arr = new int[n+1][n+1];
        for(int i=1; i<n+1; i++) {
            arr[i][i] = 1;
        }
        for(int i=0; i<m; i++) {
            st = new StringTokenizer(br.readLine());
            int a1 = Integer.parseInt(st.nextToken());
            int a2 = Integer.parseInt(st.nextToken());

            arr[a1][a2]=1;
            arr[a2][a1]= -1;
        }

        for(int k=1; k<n+1; k++) {
            for(int i=1; i<n+1; i++) {
                for(int j=1; j<n+1; j++) {
                    if(arr[i][k] == 1 && arr[k][j] ==1) {
                        arr[i][j] =1;
                    }

                    if(arr[i][k] == -1 && arr[k][j] == -1) {
                        arr[i][j] = -1;
                    }
                }
            }
        }

        for(int i=1; i<n+1; i++) {
            int cnt=0;
            for(int j=1; j<n+1; j++) {
                if(arr[i][j] != 0) {
                    cnt++;
                }
            }
            sb.append((n-cnt)+"\n");

        }
        System.out.println(sb.toString());
    }


}