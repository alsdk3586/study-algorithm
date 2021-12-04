#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;
#define MAX 101

const int INF = 999999;
int N, M;
int arr[MAX][MAX];
vector<tuple<int,int,int>> v;

//왕복 시간 정렬 후, 건물 번호 작은 것 정렬 (직접 구현)
bool compare(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    if(get<2>(a) == get<2>(b)) {
        if(get<0>(a) == get<0>(b))
            return get<1>(a) < get<1>(b);
        return get<0>(a) < get<0>(b);
    }
    return get<2>(a) < get<2>(b);
}

int main() {
    cin >> N >> M;

    //길 없음을 표시
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            arr[i][j]=INF;
            if(i==j) arr[i][i]=0;
        }
    }

    //길 있음을 표시
    for(int i=0; i<M;i++) {
        int x,y;
        cin >> x >> y;
        arr[x][y]=arr[y][x]=1;
    }

    //플로이드 와샬
    for(int k=1;k<=N;k++)  //k = 거쳐가는 노드
        for(int i=1;i<=N;i++)  // i = 출발 노드
            for(int j=1; j<=N;j++)  // j = 도착 노드
                if(arr[i][j] > arr[i][k] + arr[k][j]) //더 작은 값
                    arr[i][j] = arr[i][k] + arr[k][j];

    for(int i=1;i<N;i++) {
        for(int j=i+1;j<=N;j++) {
            int distance=0;
            for(int k=1;k<=N;k++) {
                distance += min(arr[k][i], arr[k][j])*2; //거리
            }
            //(건물번호, 건물번호, 총 거리) 배열에 저장
            v.push_back({i,j,distance});
        }
    }

    //크기 정렬!! (compare 직접 구현)
    sort(v.begin(),v.end(),compare);
    //가장 작은 값 출력
    cout << get<0>(v[0]) << " " << get<1>(v[0]) << " " << get<2>(v[0]);
}