#include <iostream>

using namespace std;
#define MAX 401

const int INF = 999999;
int V, E, result = INF;
int arr[MAX][MAX];

int main() {
    cin >> V >> E;
    
    //길 없음을 표시
    for(int i=1;i<=V;i++)
        for(int j=1;j<=V;j++)
            arr[i][j]=INF;
    //길 있음을 표시
    for(int i=0;i<E;i++) {
        int x,y,z;
        cin >> x>> y >> z;
        arr[x][y] = z;
    }
    //플로이드 와샬
    for(int k=1;k<=V;k++)  //k = 거쳐가는 노드
        for(int i=1;i<=V;i++)  // i = 출발 노드
            for(int j=1; j<=V;j++)  // j = 도착 노드
                if(arr[i][j] > arr[i][k] + arr[k][j]) //더 작은 값
                    arr[i][j] = arr[i][k] + arr[k][j];
    //다시 시작점으로 돌아온 값 중 가장 작은 값 갱신
    for(int i=1;i<=V;i++)
        result = min(result, arr[i][i]);
    //결과 출력
    cout << ((result == INF) ? -1:result);
}