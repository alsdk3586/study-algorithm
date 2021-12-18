import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

// boj_2623_음악프로그램
/* 문제풀이 방법
 * - 위상정렬문제이고 이문제 역시 스페셜 저지이므로 답이되는 아무거나 출력해주면 된다.
 * 이 문제를 풀면서 고민했던점은 인풋처리, 위상정렬 사이클 처리이다.
 *
 * 먼저 인풋처리는 예제입력을 통해 설명해보면
 * 6 3
 * 3 1 4 3  =>   1->4->3
 * 4 6 2 5 4  => 6->2->5->4
 * 2 2 3 =>  2->3
 *
 *  위와같은 순서를 갖어야 한다.
 *  1->4->3 을 보면 1->4, 4->3으로 쪼개서 4번 가수는 첫번째 비교(1->4)에서는 늦게 출연해야되고, 두번째 비교(4->3)에서는 먼저 출연해야 된다.
 *  따라서, 반복문을 돌때 변수를 재사용하면 된다.
 *
 *  사이클의 경우는
 *  - 위상정렬를 모두 돌았을때 in배열에 값이 0이아닌 값이 있으면 사이클이 존재한다고 판단할 수 있다.
 *   예를들어보자.
 *   1->2
 *   2->3
 *   3->1
 *   4->2
 *
 *   위 케이스는 1->2->3->1 로 사이클이 만들어지는 케이스인데 이 경우를 위상정렬을 돌려보면
 *   step1. 4를 q에 push
 *   step2. q.pop() & 4->2이므로 2의 in-- (2->1)
 *   step3. 위상정렬이 완료(q.empty)가 되었는데 in값이 0이 아닌 값이 존재  => 사이클이 있다고 판단.
 */

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


