//
// Created by Sujin Kim on 21. 3. 30..
//

#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

int gi[102][102] = {0};
int bo[102][102] = {0};
int SIZE;  // n

bool checkGi(int x, int y) {
    return (y == 1) or  // 바닥 위에 있을 때
           (bo[x - 1][y] or bo[x][y]) or  // 보의 한쪽 끝 부분 위에 있을 때
           (gi[x][y - 1]);   // 다른 기둥 위에 있을 때
}

bool checkBo(int x, int y) {
    return (gi[x][y - 1]) or  // 왼쪽 끝이 기둥과 연결 되어 있을 때
           (gi[x + 1][y - 1]) or  // 오른쪽 끝이 기둥과 연결 되어 있을 때
           (bo[x - 1][y] and bo[x + 1][y]);  // 양쪽 끝 부분이 다른 보와 동시에 연결되어 있을 때
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    SIZE = n;

    for (auto& frame : build_frame) {
        int x = frame[0] + 1;  // x 좌표
        int y = frame[1] + 1;  // y 좌표
        int a = frame[2];  // 기둥 - 0, 보 - 1
        int b = frame[3];  // 삭제 - 0, 설치 - 1

        // 설치
        if (a == 0 and b == 1 and checkGi(x, y)) gi[x][y] = 1;  // 기둥
        if (a == 1 and b == 1 and checkBo(x, y)) bo[x][y] = 1;  // 보

        // 기둥 삭제
        if (a == 0 and b == 0) {
            bool can = true;
            gi[x][y] = 0;

            if (gi[x][y + 1] and !checkGi(x, y + 1)) can = false;  // 다른 기둥이 위에 있을 때
            else if (bo[x - 1][y + 1] and !checkBo(x - 1, y + 1)) can = false;  // 왼쪽에 보가 있을 때
            else if (bo[x][y + 1] and !checkBo(x, y + 1)) can = false;  // 오른쪽에 보가 있을 때

            if (!can) gi[x][y] = 1;
        }
        // 보 삭제
        if (a == 1 and b == 0) {
            bool can = true;
            bo[x][y] = 0;

            if (gi[x][y] and !checkGi(x, y)) can = false;  // 왼쪽에 기둥이 있을 때
            else if (gi[x + 1][y] and !checkGi(x + 1, y)) can = false;  // 오른쪽에 기둥이 있을 때
            else if (bo[x - 1][y] and !checkBo(x - 1, y)) can = false;  // 왼쪽에 보가 있을 때
            else if (bo[x + 1][y] and !checkBo(x + 1, y)) can = false;  // 오른쪽에 보가 있을 때

            if (!can) bo[x][y] = 1;
        }
    }


    for (int x = 1; x <= n + 1; x++)
        for (int y = 1; y <= n + 1; y++) {
            if (gi[x][y]) answer.push_back(vector<int> { x - 1, y - 1, 0 });
            if (bo[x][y]) answer.push_back(vector<int> { x - 1, y - 1, 1 });
        }

    return answer;
}