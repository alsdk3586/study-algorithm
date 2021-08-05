#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 11

int N, K, arr[MAX][MAX], result=9999999;
bool visited[MAX];

//idx = 현재 행성
//dist = 현재 행성까지 거리
//planet = 방문한 행성 수
void dfs(int idx, int dist, int planet) {
	if (result < dist) return; //최솟값이 아니라면 무시
	if (planet == N) { //모든 행성 방문완료 시
		result = min(result, dist); //최솟값 갱신
		return;
	}
	for (int i = 0; i < N; i++) {
		if (visited[i]) continue; //방문 행성 무시
		visited[i] = true; //방문 표시
		dfs(i, dist + arr[idx][i], planet + 1); //dfs 탐색
		visited[i] = false;
	}
}

int main() {
    cin >> N >> K;

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            cin >> arr[i][j];

    visited[K]=true; //시작점 방문 체크

    //플로이드 와샬
    for(int k=0;k<N;k++)  //k = 거쳐가는 노드
        for(int i=0;i<N;i++)  // i = 출발 노드
            for(int j=0; j<N;j++)  // j = 도착 노드
                if(arr[i][j] > arr[i][k] + arr[k][j]) //더 작은 값
                    arr[i][j] = arr[i][k] + arr[k][j];

    dfs(K,0,1);
    
    cout << result;
}