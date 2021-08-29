#include <iostream>

using namespace std;
#define MAX 51

int N, M;
int r, c, d;
int result=0;
int arr[MAX][MAX];
bool visited[MAX][MAX];

int dr[] = {-1,0,1,0};
int dc[] = {0,1,0,-1};

int main() {
    cin >> N >> M;

    cin >> r >> c >> d;

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            cin >> arr[i][j];

    while(true) {
        if(!visited[r][c]) result++; //청소
        visited[r][c] = true;

        bool flag = true; //아직 청소 안 함

        for(int i=1;i<=4;i++) {
            int nd = (4+d-i)%4;
            int nr = r + dr[nd];
            int nc = c + dc[nd];

            if(visited[nr][nc] || arr[nr][nc]) continue; //방문했거나 벽이면 처음으로

            flag = false; //청소했음을 표시
            r = nr; c = nc; d = nd;
            break;
        }

        if(flag) { //청소를 안 했다 (청소할 곳이 없음)
            //후진
            int nr = r + dr[(d+2)%4];
            int nc = c + dc[(d+2)%4];

            if(arr[nr][nc]) break; //후진시 벽이면 종료
            else {
                //벽이 아니면 후진
                r = nr;
                c = nc;
            }
        }
    }

    cout << result;
}