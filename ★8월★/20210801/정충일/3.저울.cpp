#include <iostream>

using namespace std;
#define MAX 101

int N, M, cnt;
int arr[MAX][MAX];

int main() {
    cin >> N >> M;

    for(int i=0;i<M;i++) {
        int a,b;
        cin >> a >> b;

        arr[a][b]=1; // 갈 수 있다고 표시
    }

    //플로이드 와샬
    for(int k=1;k<=N;k++) { //k = 거쳐가는 노드
        for(int i=1;i<=N;i++) { // i = 출발 노드
            for(int j=1; j<=N;j++) { // j = 도착 노드
                if(arr[i][k] && arr[k][j]) //만약 거쳐갈 수 있다면
                    arr[i][j] = 1; // 갈 수 있다고 표시
            }
        }
    }

    for(int i=1;i<=N;i++) {
        cnt=0; //초기화
        for(int j=1;j<=N;j++) {
            if(!arr[i][j] && !arr[j][i]) cnt++; //갈 수 없다면 count up
        }
        cout << cnt-1 << "\n"; //바로 출력
    }
}