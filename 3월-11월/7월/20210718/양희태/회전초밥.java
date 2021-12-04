public class Main {

    static int N, D, K, C, dishes[];
    static int eaten[];

    static BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(input.readLine());
        N = Integer.parseInt(st.nextToken());    // 접시
        D = Integer.parseInt(st.nextToken());    // 초밥
        K = Integer.parseInt(st.nextToken());    // 연속해서 먹는 접시
        C = Integer.parseInt(st.nextToken());    // 서비스 초밥

        dishes = new int[N];
        eaten = new int[D + 1];

        for (int i = 0; i < N; i++) {
            dishes[i] = Integer.parseInt(input.readLine());
        }
        System.out.println(belt());
    }

    private static int belt() {
        int max = 0, kind = 0;

        // 0~K개의 초밥을 윈도우에 포함시키고 시작
        for (int i = 0; i < K; i++) {
            int sushi_no = dishes[i]; // 초밥 번호
            if (eaten[sushi_no] == 0) kind++; // 초밥이 처음먹는 것이면 종류 수

            eaten[sushi_no]++; // 해당 번호의 초밥 개수 증가
        }

        // 맨 처음에 먹은 초밥 종류가 최대 종류
        max = kind;

        // 왼쪽에서부터 하나씩 윈도우에서 제외시키고 오른쪽 초밥을 윈도우에 포함시키면서 이동
        for (int i = 1; i < N; i++) {
            //왼쪽 초밥 처리
            int front = dishes[i - 1];    // 빠질 초밥위치
            eaten[front]--;            // front 위치에 있던 초밥 번호의 먹은 횟수를 -1
            if (eaten[front] == 0)        // 먹은 횟수를 뺐더니 0이 되었다면 종류도 -1
                kind--;

            // 오른쪽 초밥 처리
            int end = (i + K - 1) % N;
            int sushi_no = dishes[end];
            if (eaten[sushi_no] == 0)
                kind++;
            eaten[sushi_no]++;

            // 먹은 종류가 많아지거나 같은 경우 쿠폰 반영해서 max 값 갱신
            if (max <= kind) {
                if (eaten[C] == 0)    // 쿠폰 초밥을 안먹은 경우 종류 +1
                    max = kind + 1;
                else
                    max = kind;
            }
        }
        return max;
    }
}