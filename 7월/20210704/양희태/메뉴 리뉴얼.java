import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

/**
 * 그리디 알고리즘
 * 0 ~ N-1까지 linkedlist에 숫자 초기화
 * 인덱스 대로 int배열 생성(line)
 * 키 큰 사람 수 입력
 * linkedList remove 결과을 줄 선 순서
 */
public class Main {

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());

        List<Integer> idx = new LinkedList<>();
        int[] line = new int[n];

        for (int i = 0; i < n; i++) {
            idx.add(i);
        }

        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= n; i++) {
            int p = Integer.parseInt(st.nextToken());
            int j = idx.remove(p);
            line[j] = i;
        }
        for (int ans : line) {
            System.out.print(ans + " ");
        }

    }
}
