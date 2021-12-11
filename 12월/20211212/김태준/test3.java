package com.company;

import java.util.*;

// n과 m
// n개중 m개를 선택한다.
// 조건
//  - 중복된 수열 제거 -> hashMap 사용
//  - 사전 순으로 증가하는 순으로 출력 -> dfs를 돌리기전 input 배열을 오름차순으로 정렬
// 주의할 점
//  - dfs return 조건 (m개중 n개를 다 골랐을때)에서 바로 System.out.println으로 출력하면 시간초과...
//  map에 담에서 마지막에 한번만 출력한다. io 시간때문에 시간초과 발생하는거 같음

public class test4 {

    static int n;
    static int m;
    static int in[ ];
    static int res[ ];
    static Map<String, Integer> permutationMap = new HashMap<>();
    static StringBuilder resSbBuilder = new StringBuilder();

    public static void main(String args[ ]) {

        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();

        res = new int[m];
        in = new int[n];

        for(int i=0; i<n; i++) {
            int input = sc.nextInt();
            in[i] = input;
        }
        Arrays.sort(in);

        //n개중 m개 선택
        dfs(0);
        System.out.println(resSbBuilder.toString());
    };

    static void dfs(int d) {

        if(d == m) {
            StringBuilder sb = new StringBuilder();
            for(int i=0; i<d; i++) {
                sb.append(res[i]);
                sb.append(" ");
            }
            sb.deleteCharAt(sb.length() - 1);

            String pKey = sb.toString();
            if(!permutationMap.containsKey(pKey)) {
                permutationMap.put(pKey, 1);
                resSbBuilder.append(pKey);
                resSbBuilder.append("\n");
            }
            return;
        }

        for(int i=0; i<n; i++) {
            res[d] = in[i];
            dfs(d+1);
        }
    }
}


