#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <cstring>

using namespace std;

vector<deque<int>> gearWheels(5);
int rotation[5];
bool flag[5];

void setRotation(int number, int direction) {
    rotation[number] = direction;
    flag[number] = true;
    // 현재 톱니바퀴의 왼쪽 톱니바퀴 세팅
    if (number - 1 > 0 && !flag[number - 1]) {
        // 현재 톱니바퀴가 회전하지 않으면
        if (direction == 0) setRotation(number - 1, 0);
        // 맞닿은 극이 같다면
        else if (gearWheels[number][6] == gearWheels[number - 1][2])
            setRotation(number - 1, 0);
        // 맞닿은 극이 다르면
        else setRotation(number - 1, -direction);
    }
    // 현재 톱니바퀴의 오른쪽 톱니바퀴 세팅
    if (number + 1 <= 4 && !flag[number + 1]) {
        // 현재 톱니바퀴가 회전하지 않으면
        if (direction == 0) setRotation(number + 1, 0);
        // 맞닿은 극이 같다면
        else if (gearWheels[number][2] == gearWheels[number + 1][6])
            setRotation(number + 1, 0);
        // 맞닿은 극이 다르면
        else setRotation(number + 1, -direction);
    }
}

void rotate() {
    for (int i = 1; i <= 4; i++) {
        if (rotation[i] == 0) continue;
        // 시계 방향 회전
        if (rotation[i] == 1) {
            int temp = gearWheels[i].back();
            gearWheels[i].pop_back();
            gearWheels[i].push_front(temp);
        } else { // 반시계 회전
            int temp = gearWheels[i].front();
            gearWheels[i].pop_front();
            gearWheels[i].push_back(temp);
        }
    }
}

int getScore() {
    int result = 0;
    for (int i = 1; i <= 4; i++) {
        // 12시 방향이 S극
        if (gearWheels[i][0] == 1)
            result += pow(2, i - 1);
    }
    return result;
}

int main() {
    for(int i=1;i<=4;i++) {
        for(int j=0;j<8;j++) {
            char x;
            cin >> x;
            gearWheels[i].push_back(x-'0');
        }
    }

    int T;
    cin >> T;

    while(T--) {
        int number, direction;
        cin >> number >> direction;
        memset(flag, false, sizeof(flag));
        setRotation(number, direction);
        rotate();
    }
    int result = getScore();
    cout << result;
}