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

        int singerCnt;
        int singer;
        int prevSinger;
        for(int i=0; i<m; i++) {
            singerCnt = scanner.nextInt();
            prevSinger=0;

            for(int j=0; j<singerCnt; j++) {
                singer = scanner.nextInt();

                if(prevSinger == 0) {
                    prevSinger = singer;
                    continue;
                }

                List<Integer> singerList = edgeMap.get(prevSinger);

                if(singerList == null) {
                    singerList = new ArrayList<>();
                }

                in[singer]++;
                singerList.add(singer);
                edgeMap.put(prevSinger, singerList);
                prevSinger = singer;
            }
        }


        for(int i=1; i<=n; i++) {
            if(in[i] == 0) {
                q.add(i);
            }
        }
    }

    public static void topologicalSort() {

        while(!q.isEmpty()) {
            int top = q.poll();
            resSb.append(top + "\n");
            List<Integer> singerList = edgeMap.get(top);

            if(singerList != null) {
                for(int i=0; i<singerList.size(); i++) {
                    int singer = singerList.get(i);

                    in[singer]--;
                    if(in[singer] == 0) q.add(singer);
                }
            }
        }

        if(isCyle()) {
            System.out.print(0);
            System.exit(0);
        }

    }

    public static boolean isCyle( ) {
        for(int i=1; i<=n; i++) {
            if(in[i] != 0) return true;
        }

        return false;
    }

    public static void printRes( ) {
        System.out.println(resSb.toString());
    }
}


