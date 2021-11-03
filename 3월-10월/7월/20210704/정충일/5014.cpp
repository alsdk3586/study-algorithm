#include <iostream>
#include <queue>

using namespace std;
#define MAX 1000001

int F, S, G, U, D;
int dx[2];
int visit[MAX]={0,};
bool flag=true;

void bfs() {
    queue<int> q;
    q.push(S);
    visit[S]=1;

    while(!q.empty()) {
        S = q.front();
        q.pop();

        for(int i=0;i<2;i++) {
            int nx = S + dx[i];
            
            if(nx>0 && nx<=F) {
                if(visit[nx]==0) {
                    visit[nx]=visit[S]+1;
                    q.push(nx);
                }
            }
            if(S==G) {
                flag=false;
                break;
            }
        }
    }
}

int main() {
    cin >> F >> S >> G >> U >> D;

    dx[0]=U;
    dx[1]=-D;
    
    bfs();

    if(flag) cout << "use the stairs";
    else cout << visit[G]-1;
}