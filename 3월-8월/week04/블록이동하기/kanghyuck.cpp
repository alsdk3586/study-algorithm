/* 블록 이동하기, kang-hyuck */
#include <string>
#include <vector>
#include <queue>
#include <tuple>  // tie()
using namespace std;

typedef struct RobotInfo{
    int y,x, dir,cnt;
}RobotInfo;

// 전역변수
int visited[110][110][4];  // [][][방문시방향]
int dx[4] = {-1, 0, 1, 0};
int dy[4] = { 0,-1, 0, 1};
// [현재모양][회전방향][확인필요한칸] ("회전축 위치 기준" 인덱스 차이)
int dxCheck[4][2][2] = { {{-1, 0},{-1, 0}},  {{ 1, 1},{-1,-1}},  {{ 1, 0},{ 1, 0}},  {{-1,-1},{ 1, 1}} };
int dyCheck[4][2][2] = { {{-1,-1},{ 1, 1}},  {{-1, 0},{-1, 0}},  {{ 1, 1},{-1,-1}},  {{ 1, 0},{ 1, 0}} };
int ddir[2] = {1, 3};  // 다음 회전 방향 계산시 사용 (더하는 값)
int N, ans;
queue<RobotInfo> q;
vector<vector<int>> map;

// 함수선언
void BFS(void);
bool OutOfRange(int,int, int);
bool Finish(int,int, int);
bool CrashWall(int, int, int);
bool CrashWallRotate(int, int, int, int);


int solution(vector<vector<int>> board)
{
    // 전역변수 초기화
    N = (int)board.size();  // 세로 크기 저장.
    map = board;

    // 실행부
    BFS();

    // 출력부
    return ans;
}


void BFS(void)
{
    int i, y,x,yy,xx,dir,dirNext,dirL,cnt;

    // 초기화
    visited[0][1][0];
    q.push({0,1, 0,0});  // "오른쪽 위치" 기준으로 이동.

    // 실행부
    while(!q.empty())
    {
        tie(yy,xx,dir,cnt) = {q.front().y, q.front().x, q.front().dir, q.front().cnt};
        q.pop();


        // 종료조건
        if(Finish(yy,xx,dir)){ans=cnt; return;}  // 목표 지점에 도달한 경우


        // ------- 자식 노드 호출 --------
        // 1. 이동 (다른 위치로)
        for(i=0; i<4; i++)
        {
            // 다음 이동할 위치 계산
            y=yy+dy[i]; x=xx+dx[i];

            // 이동할 수 없는 경우
            if(OutOfRange(y,x, dir)) continue;  // 맵을 벗어나는 경우
            if(visited[y][x][dir] == 1) continue;  // 방문한 적이 있는 경우
            if(CrashWall(y,x,dir)) continue;  // 벽인 경우

            // 이동할 수 있는 경우
            visited[y][x][dir]=1;  // 방문표시
            q.push({y,x,dir,cnt+1});
        }
        // 2. 회전1 (현재 위치가 고정 - 회전축 역할)
        for(i=0; i<2; i++)  // 회전가능방향 2방향
        {
            // 다음 회전 방향 계산
            dirNext = (dir + ddir[i])%4;

            // 회전할 수 없는 경우
            if(OutOfRange(yy,xx, dirNext)) continue;  // 맵을 벗어나는 경우 (회전 하려는 곳이.)
            if(visited[yy][xx][dirNext] == 1) continue;  // 방문한 적이 있는 경우
            if(CrashWallRotate(yy,xx,dir, i)) continue;  // 벽에 부딪히는 경우 (회전 도중에.)

            // 회전할 수 있는 경우
            visited[yy][xx][dirNext]=1;  // 방문표시
            q.push({yy,xx,dirNext,cnt+1});
        }
        // 3. 회전2 (현재 위치가 회전)
        for(i=0; i<2; i++)
        {
            // 왼쪽 위치 계산 (회전축 역할)
            int Ly=yy+dy[dir], Lx=xx+dx[dir];

            // 다음 회전 방향 계산
            dirL    = (dir+2)%4;  // L,R 역할이 바뀐 것을 의미 (고정축 기준이 바뀐 것을 의미)
            dirNext = (dirL + ddir[i])%4;

            // 회전할 수 없는 경우
            if(OutOfRange(Ly,Lx, dirNext)) continue;  // 맵을 벗어나는 경우 (회전 하려는 곳이.)
            if(visited[Ly][Lx][dirNext] == 1) continue;  // 방문한 적이 있는 경우
            if(CrashWallRotate(Ly,Lx,dirL, i)) continue;  // 벽에 부딪히는 경우 (회전 도중에.)

            // 회전할 수 있는 경우
            visited[Ly][Lx][dirNext]=1;  // 방문표시
            q.push({Ly,Lx,dirNext,cnt+1});  // 참고로. 오른쪽 위치가 Ly,Lx로 여겨지고 큐에 들어간다.
        }
    }
}

bool OutOfRange(int y, int x, int dir){
    int Ly=y+dy[dir], Lx=x+dx[dir];  // 왼쪽 위치 계산
    if(y<0  || x<0  || y>=N  || x >=N) return true;  // (오른쪽) 맵을 벗어나는 경우
    if(Ly<0 || Lx<0 || Ly>=N || Lx>=N) return true;  // (왼쪽)   맵을 벗어나는 경우
    return false;  // 맵을 벗어나지 않는 경우
}

bool Finish(int y, int x, int dir){
    int Ly=y+dy[dir], Lx=x+dx[dir];  // 왼쪽 위치 계산
    if((y==N-1 && x==N-1) || (Ly==N-1 && Lx==N-1)) return true;  // 왼쪽 || 오른쪽 이 (N-1,N-1)에 도달한 경우
    return false;
}

bool CrashWall(int y, int x, int dir){
    int Ly=y+dy[dir], Lx=x+dx[dir];  // 왼쪽 위치 계산
    if(map[y][x]   == 1) return true;  // (오른쪽) 벽에 부딪히는 경우
    if(map[Ly][Lx] == 1) return true;  // (왼쪽)   벽에 부딪히는 경우
    return false; // 벽에 부딪히지 않는 경우
}

bool CrashWallRotate(int yy, int xx, int curDir, int rotDir){
    int i, y,x;
    for(i=0; i<2; i++){
        // 회전시 벽 유/무 확인할 위치 계산
        y=yy+dyCheck[curDir][rotDir][i];  x=xx+dxCheck[curDir][rotDir][i];

        // 벽에 부딪히는 경우
        if(map[y][x]==1) return true;
    }

    // 벽에 부딪히지 않는 경우
    return false;
}
