/* 기둥과 보 설치, kang-hyuck */
#include <vector>
#include <tuple>  // tie()
using namespace std;

// 전역변수
vector<vector<int>> answer;
vector<vector<int>> command;
int map[1010][1010];
int N;

// 함수선언
void Start(void);
bool CannotInstall(int, int, int);
bool CannotRemove(int, int, int);
bool OutOfRange(int, int);
bool Exist(int, int, int);


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {

    // 전역변수 초기화
    N = build_frame.size(); // 세로 크기 저장
    command = build_frame;  // 명령어 커맨드 저장

    // 실행부
    Start();

    // 출력부
    for(int j=0; j<N; j++) for(int i=0; i<N; i++) for(int k=0; k<2; k++) if( map[i][j]&(1<<k) ) answer.push_back({j,i,k});
    return answer;
}


void Start(void)
{
    int i, y,x,item,cmd;

    // 명령 갯수 만큼 실행
    for(i=0; i<(int)command.size(); i++)
    {
        tie(x,y,item,cmd) = {command[i][0], command[i][1], command[i][2], command[i][3]};

        // 설치하는 경우
        if(cmd==1)
        {
            // 설치할 수 없는 경우
            if(map[y][x]&(1<<item)) continue;  // 이미 설치 되어 있는 경우
            if(CannotInstall(y,x,item)) continue;  // 설치할 수 없는 조건인 경우

            // 설치할 수 있는 경우
            map[y][x] |= (1<<item);  // 맵에 표시
        }

        // 제거하는 경우
        else if(cmd==0)
        {
            // 제거할 수 없는 경우
            if( !(map[y][x]&(1<<item)) ) continue;  // 설치되지 않은 경우
            if(CannotRemove(y,x,item)) continue;  // 제거할 수 없는 조건인 경우

            // 제거할 수 있는 경우
            map[y][x] &= ~(1<<item);  // 비트마스킹. 해당 비트만 지워줌
        }
    }
}

bool CannotInstall(int y, int x, int item)
{
    // 기둥을 못세우는 경우
    if(item==0){
        if(OutOfRange(y,x))  return true;  // 맵을 벗어나는 경우 (기둥 세우려는 위치가.)
        if( y!=0 && !(Exist(y,x-1,1) || Exist(y,x,1) || Exist(y-1,x,0)) ) return true;  // 양쪽 1곳도 보(1)가 없고, 아래층에도 기둥(0)도 없는 경우
    }

    // 보를 못세우는 경우
    else if(item==1)
    {
        if(OutOfRange(y,x))   return true;  // 맵을 벗어나는 경우 (보 세우려는 위치가.)
        if( y!=0 && !(Exist(y-1,x,0) || Exist(y-1,x+1,0) || (Exist(y,x-1,1)&&Exist(y,x+1,1)) ) ) return true;  // 양쪽 기둥이 1곳도 없거나 || 양쪽 동시에 보가 없는 경우
    }

    // 기둥|보를 세울 수 있는 경우
    return false;
}

bool CannotRemove(int y, int x, int item)
{
    // 기둥을 제거할 수 없는 경우
    if(item==0)
    {
        // 일단 제거해본다.
        if(OutOfRange(y,x)) return true;  // 맵 내에 위치가 존재하는 지 확인
        map[y][x] &= ~(1<<item);  // 해당 위치에서 기둥 제거

        // 설치할 수 없는 것이 있는 지 확인
        if( Exist(y+1,x,1)   && CannotInstall(y+1,x,1) )  {map[y][x] |= (1<<item); return true;}   // 위,오른쪽 보
        if( Exist(y+1,x-1,1) && CannotInstall(y+1,x-1,1) ){map[y][x] |= (1<<item); return true;}   // 위,왼쪽 보
        if( Exist(y+1,x,0)   && CannotInstall(y+1,x,0) )  {map[y][x] |= (1<<item); return true;}   // 위쪽 기둥
    }

    // 보를 제거할 수 없는 경우
    else if(item==1)
    {
        // 일단 제거해본다.
        if(OutOfRange(y,x)) return true;  // 맵 내에 위치가 존재하는 지 확인
        map[y][x] &= ~(1<<item);  // 해당 위치에서 보 제거

        // 설치할 수 없는 것이 있는 지 확인
        if( Exist(y,x-1,1) && CannotInstall(y,x-1,1) ) {map[y][x] |= (1<<item); return true;}  // 왼쪽 보
        if( Exist(y,x+1,1) && CannotInstall(y,x+1,1) ) {map[y][x] |= (1<<item); return true;}  // 오른쪽 보
        if( Exist(y,x,0)   && CannotInstall(y,x,0) )   {map[y][x] |= (1<<item); return true;}  // 왼쪽 기둥
        if( Exist(y,x+1,0) && CannotInstall(y,x+1,0) ) {map[y][x] |= (1<<item); return true;}  // 오른쪽 기둥
    }

    // 기둥|보를 제거할 수 있는 경우
    return false;
}

bool Exist(int y, int x, int item){
    if( !OutOfRange(y,x) && (map[y][x]&(1<<item)) ) return true;   // 해당 위치가 맵 내에 있고 || 해당 위치에 item이 존재한다면
    return false;
}

bool OutOfRange(int y, int x){
    if(y<0 || x<0 || y>=N || x>=N ) return true;  // 맵을 벗어나는 경우
    return false;  // 맵 벗어나지 않는 경우
}
