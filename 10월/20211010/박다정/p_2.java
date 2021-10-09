import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

public class b_1174 {
    private static final ArrayList<Long> list = new ArrayList<>();

    public static void rec(int n, int digit, int index, String current) {
        if (current.charAt(current.length() - 1) == '0') {
            list.add(Long.valueOf(current));
            return;
        }

        if (Long.valueOf(current) > 9) {
            list.add(Long.valueOf(current));
        }

        for (int i = digit; i > -1; i -= 1) {
            if (i - 1 > -1) {
                rec(n, i - 1, index + 1, current + Integer.toString(i - 1));
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());

        if (n > 1023) {
            System.out.println(-1);
            return;
        }

        for (int i = 1; i < 10; i += 1) {
            list.add(Long.valueOf(i));
            rec(n, i, 0, Integer.toString(i));
        }

        list.add(0L);
        Collections.sort(list);
        System.out.println(list.get(n - 1));
    }
}
