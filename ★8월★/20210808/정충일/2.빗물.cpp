#include <iostream>
#include <vector>

using namespace std;
#define MAX 501

int H, W;
int arr[MAX];

int main() {
    cin >> H >> W; //세로길이 H, 가로길이 W

    for(int i=0;i<W;i++)
        cin >> arr[i];

    int floor = 1, stack = 0, indx = 0, flag = 0, result = 0;
    //floor = 층
    //stack = 물 임시 저장
    //flag = 벽을 만난 횟수
    //result = 결괏값

    while(floor < H+1) { //층만큼 반복한다.
        if(arr[indx] >= floor) flag++; //현재 층보다 값이 크다면 벽
        else if(arr[indx] < floor) { // 현재 층 보다 값이 작은데
            if(flag) { // 벽을 만났었다면, 물 채우고 현재 층과 같은 값을 넣어준다.
                stack++; arr[indx]++;
            } else arr[indx]++; // 벽을 안 만났다면, 물 안 채운다.
        }

        indx++; //다음 블록
    
        if(flag == 2) { // 벽을 두번 만났다면
            flag--; // 다음 벽이 존재할지도 모르니 값을 하나 줄여준다.
            result+=stack; // stack에 쌓인 값을 결괏값에 갱신
            stack = 0; // 넣었으니 초기화
        }

        if(indx == W) { //현재층에 모든 블록을 방문했다면
            floor++; stack = 0; indx = 0; flag = 0;
        } //초기화 후 다음층으로!
    }
    
    cout << result; // 결괏값 출력
}