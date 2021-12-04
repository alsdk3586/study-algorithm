package com.company.algorithm_solving.study;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class test3 {

/*
    static int map[ ][ ] = {{0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 1, 0, 6, 0},
                            {0, 0, 0, 0, 0, 0}};
*/
/*
    static int map[ ][ ] = {{0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 6, 0},
    {0, 6, 0, 0, 2, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 5}};
*/

/*
static int map[ ][ ] = {{1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1}};
*/
/*
static int map[ ][ ] = {{1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 5, 0, 0},
        {0, 0, 5, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1}};
*/

//static int map[ ][ ] = {{0, 1, 2, 3, 4, 5, 6}};
/*
static int map[ ][ ] = {{4, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4}};
*/

    static int map[][];
    static int dx[] = {-1, 0, 1, 0 };
    static int dy[] = {0, 1, 0, -1};
    static int n;
    static int m;
    static int visit[][];
    static int res = 64;
    static List<CCTV> cctvList = new ArrayList<>();

    public static void main(String args[ ]) {
        // 백준 15683번 감시
        // https://www.acmicpc.net/problem/15683

        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        map = new int[n][m];
        visit = new int[n][m];
        
        for(int i=0; i<n; i++) {
            Arrays.fill(visit[i], 0);
        }


        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                map[i][j] = sc.nextInt();
                int v = map[i][j];
                if(1<=v && v <=5) {
                    visit[i][j] = 1;
                    cctvList.add(new CCTV(i, j, v));
                }
                if(v == 6) visit[i][j] = 1;
            }
        }

       dfs(0);
        System.out.println(res);
    }

    static void dfs(int d) {

        if(d == cctvList.size()) {
            res = Math.min(res, calInvisibleArea());
            return;
        }

        CCTV cctv = cctvList.get(d);
        // 방향설정
        for(int i=0; i<4; i++) {
            fillAndClearMapBranchProcessing(cctv, cctv.type, i);
            dfs(d+1);
            fillAndClearMapBranchProcessing(cctv, 0, i);
        }
    }

    // 설정된 방향으로 type 기반 map을 채워주기 위한 전처리
    static void fillAndClearMapBranchProcessing(CCTV cctv, int clearValue, int direction) {
        int type = cctv.type;

        if(type==1) fillAndClearMap(cctv, clearValue, direction);
        else if(type==2) {
            if (direction == 2 || direction == 3) return;
            fillAndClearMap(cctv, clearValue, direction);
            fillAndClearMap(cctv, clearValue, direction + 2);
        } else if(type==3) {
            fillAndClearMap(cctv, clearValue, direction);
            fillAndClearMap(cctv, clearValue, (direction + 1) % 4);
        } else if(type==4) {
            fillAndClearMap(cctv, clearValue, direction);
            fillAndClearMap(cctv, clearValue, (direction + 1) % 4);
            fillAndClearMap(cctv, clearValue, (direction + 3) % 4);
        } else if(type==5) {
            if(direction != 0) return;
            for(int i=0; i<4; i++) {
                fillAndClearMap(cctv, clearValue, direction + i);
            }
        }
    }

    // 한방향으로만 감
    static void fillAndClearMap(CCTV cctv, int clearValue, int direction) {

        int xp = cctv.xp;
        int yp = cctv.yp;

        int xp2 = xp;
        int yp2 = yp;
        // 상(0), 우(1), 하(2), 좌(3)
        while(true) {
            xp2 += dx[direction];
            yp2 += dy[direction];

            if(xp2 < 0 || n <= xp2) break;
            if(yp2 < 0 || m <= yp2) break;
            if(map[xp2][yp2] == 6) break;

            if(clearValue == 0) visit[xp2][yp2] -=1;
            else visit[xp2][yp2] += 1;
        }
    }

    // map의 사각지대 갯수
    static int calInvisibleArea( ) {
        int cnt = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(visit[i][j] == 0) cnt++;
            }
        }
        return cnt;
    }

    static class CCTV {
        int xp;
        int yp;
        int type;

        public CCTV(int xp, int yp, int type) {
            this.xp = xp;
            this.yp = yp;
            this.type = type;
        }
    }
}
