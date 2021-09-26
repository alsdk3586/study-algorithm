/* 외벽 점검, kang-hyuck  - 시간초과.ㅠ.ㅠ 64/100 */
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>  // sort(), min(), greater<int>()
using namespace std;
#define INF 987654321

// 전역변수
int N,ans;
int map[210];  // 1:weak지점
int used[10];  // 사용한 친구 확인용도 (부모 노드에서)
int dx[2] = {-1, 1};  // 0:반시계방향, 1:시계방향 이동 용도
vector<int> Weak, Dist;  // 주어진 입력을 DFS에서 사용하기 쉽도록 전역변수로 사용

// 함수선언
void DFS(int,int);
void Move(int,int,int);
bool Finish(void);
void Backup(int*);
void Reset(int*);

int solution(int n, vector<int> weak, vector<int> dist) {
    
    // 전역변수 초기화
    N=n;  Weak=weak;  Dist=dist;  ans=INF;
    for(int i=0; i<(int)weak.size(); i++) map[weak[i]]=1;  // weak지점 1로 표시
    
    // 실행부
    sort(Dist.begin(), Dist.end(), greater<int>());  // 내림차순 정렬. (DFS 탐색 경우의 수 줄어듬)
    DFS(0,0);  // (0명선택, weak 0번 인덱스 부터 해결)
    
    // 종료부
    if(ans==INF) ans=-1;  // 친구들로 해결할 수 없는 경우
    return ans;
}

void DFS(int cnt, int index)
{
    int mapBackup[210];  // 현재 위치에서 map 백업용. 확인이 끝나고 자식노드에서 현재 노드로 돌아올 경우. map값 복원용도
    
    // 종료조건
    if(cnt>=ans) return;  // cnt가 ans 이상인 경우. 굳이 더 확인할 필요가 없음
    if(Finish()){ans = min(ans, cnt);  return;}  // 끝난 경우
    if(index>=Weak.size()) return;  // 취약지점을 모두 선택한 경우
    if(cnt  >=Dist.size()) return;  // 친구들을 모두 선택한 경우
    
    // 자식 노드 호출
    // - 1. 친구를 보내는 경우
    for(int j=0; j<(int)Dist.size(); j++)  // 친구를 선택
    {
        // 친구를 보낼 수 없는 경우 (j번째 친구)
        if(used[j]==1) continue;  // 이미 친구를 어디로 보낸 경우

        // 친구를 보낼 수 있는 경우
        // - 1. 시계방향으로 보내기
        Backup(mapBackup);  used[j]=1;  // 현재 map 값을 백업, 사용됨 표시            
        Move(index, Dist[j], 1); // 시계방향 시뮬레이션
           DFS(cnt+1, index+1);  // (사람수+1, 해결해야할index+1)
        Reset (mapBackup);  // map 복원
        // - 2. 반시계방향으로 보내기
        Move(index, Dist[j], 0);  // 반시계방향 시뮬레이션
           DFS(cnt+1, index+1);  // (사람수+1, 해결해야할index+1)
        Reset (mapBackup);  used[j]=0;
    }
    
    // - 2. 친구를 안 보내는 경우
    DFS(cnt, index+1);
}
void Move(int index, int dist, int mode){
    int x=Weak[index];  map[x]=0;  // 처음 위치 지우고 넣어줌.
    if(mode==1) while(dist--){x=x+dx[mode];  x=x%N;        map[x]=0;}  // 시계방향으로 거리만큼 이동하면서 지움
    if(mode==0) while(dist--){x=x+dx[mode];  if(x<0)x=N-1; map[x]=0;}  // 반시계방향으로 거리만큼 이동하면서 지움  
}

bool Finish(){
    for(int i=0; i<(int)Weak.size(); i++) if(map[Weak[i]]==1) return false;  // weak 지점이 모두 0이 아닌 경우
    return true;  // weak 지점이 모두 0인 경우
}
void Backup(int mapBackup[]){  for(int i=0; i<N; i++) mapBackup[i]=map[i]; }
void Reset (int mapBackup[]){  for(int i=0; i<N; i++) map[i]=mapBackup[i]; }
