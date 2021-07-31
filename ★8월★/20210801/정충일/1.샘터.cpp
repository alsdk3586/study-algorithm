#include <iostream>
#include <queue>
#include <set>

using namespace std;
typedef long long ll;

int K, N;
ll misfortune=1, result=0;
int dx[]={1,-1};
queue<int> q;
set<int> s;

ll bfs() {
    while(!q.empty()) {
        int Size = q.size(); //size가 계속 변할 수 있으므로 고정해준다
        for(int i=0; i<Size;i++) { //size만큼 반복
            int a = q.front();
            q.pop();
            for(int j=0;j<2;j++) {
                int nx = a + dx[j]; //좌우 탐색
                if(!s.count(nx)) { //값이 없다면
                    s.insert(nx); q.push(nx);//추가
                    result+=misfortune;//불행도 갱신

                    if(!--K) return result;//모든 집을 지었다면 종료
                }
            }
        }
        misfortune++; //동일한 거리 다 했으니 1 증가 후 증가한만큼의 거리, 다시 탐색
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> K;
    
    for(int i=0;i<N;i++) {
        int x;
        cin >> x;
        q.push(x); s.insert(x);
    }
    cout << bfs();
}