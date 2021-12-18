package com.company.algorithm_solving.study.week3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

// boj_14567_선수과목
/* 문제풀이 방법
 * 위상정렬로 풀면되지만 단순히 위상정렬을 출력하는 문제가 아니라 각 과목을 이수하려면 최소 몇학기가 걸리는지 구해야 한다.
 * 특정 과목을 이수하기 위한 최소 학기는 어떻게 구해야할까?
 * 문제의 테스트 케이스 2번을 바탕으로 예를들어보자
 *  - 1->2
 *    1->3
 *    2->5
 *    4->5
 *  위와 같은 선수과목 조건을 갖을때 5번과목을 이수하려면 몇학기가 걸리는지 시뮬레이션 해보면된다.
 *
 *  4->5  => 2학기
 *  1->2->5 => 3학기
 *
 *  5번과목의 선수조건을 보면 2학기 or 3학기 후에 5번 과목이수가 가능하다.
 *  그럼 2학기가 답인가?  아니다. 5번 과목을 이수하려면 4번 과목 뿐만 아니라, 1,2 과목도 모두 이수해야하므로 3학기가 답이된다.
 *  
 *  이부분이 이 문제의 핵심인데 즉, 해당 과목을 이수하려면 해당과목으로 들어오는 조건중 최대 학기가 문제의 답이된다.
 *  
 *  
 *
 * 
 * 
 */
public class test3 {

    static int n;
    static int m;
    static int in[];
    static int minSemesterArr[ ];
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
        minSemesterArr = new int[n + 1];
        Arrays.fill(in, 0);
        Arrays.fill(minSemesterArr, 0);

        int s1, s2;
        for(int i=0; i<m; i++) {
            s1 = scanner.nextInt();
            s2 = scanner.nextInt();

            List<Integer> subjectList = edgeMap.get(s1);

            if(subjectList == null) {
                subjectList = new ArrayList<>();
            }

            in[s2]++;
            subjectList.add(s2);
            edgeMap.put(s1, subjectList);
        }


        for(int i=1; i<=n; i++) {
            if(in[i] == 0) {
                q.add(i);
                minSemesterArr[i] = 1;
            }
        }
    }

    public static void topologicalSort() {

        while(!q.isEmpty()) {

            int top = q.poll();
            int semester = minSemesterArr[top];
            List<Integer> subjectList = edgeMap.get(top);

            if(subjectList != null) {
                for(int i=0; i<subjectList.size(); i++) {
                    int subject = subjectList.get(i);
                    in[subject]--;

                    minSemesterArr[subject] = Math.max(minSemesterArr[subject], semester+1);
                    if(in[subject] == 0) q.add(subject);
                }
            }
        }
    }

    public static void printRes( ) {
        StringBuilder resSb = new StringBuilder();
        for(int i=1; i<=n; i++) {
            resSb.append(minSemesterArr[i] + " ");
        }

        System.out.println(resSb.toString());
    }
}

