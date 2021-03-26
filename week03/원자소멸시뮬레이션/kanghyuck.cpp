/* 원자 소멸 시뮬레이션, kang-hyuck */
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

typedef struct AtomInfo{
    int y,x, dir,energy;   // 에너지 0이면 사라진 것으로 판단.
}AtomInfo;

// 전역변수
int T,N, ans;
int map[4010][4010];  // 해당 위치. 원자 인덱스 저장용도
AtomInfo atom[1010];  // 원자 정보. (입력 순서대로. 배열에 저장)
int dx[4] = {0, 0, -1, 1};   int dy[4] = {-1, 1, 0, 0};   //0:상 1:하 2:좌 3:우

// 함수선언
void Start(void);
void AtomMove(void);
void AtomBreak(void);
bool Finish(void);
bool OutOfRange(int, int);

int main()
{
    int t, temp1,temp2,temp3,temp4, cnt=0;

    cin>>T;
    for(t=1; t<=T; t++)
    {
        // 입력부
        cin>>N;
        for(int i=0; i<N; i++){
            cin>>temp1>>temp2>>temp3>>temp4;
            atom[cnt]={2*((-1)*temp2+1000),2*(temp1+1000),temp3,temp4};
            map[2*((-1)*temp2+1000)][2*(temp1+1000)]=temp4;    // 에너지 값 넣어놈
            cnt++;  // 원자정보 인덱스 증가.
        }

        // 실행부
        Start();

        // 출력부
        cout<<"#"<<t<<" "<<ans<<endl;

        // 초기화
        ans=0; cnt=0;  memset(map, 0, sizeof(map));
    }

    return 0;
}

void Start()
{
    while(1)
    {
        // 원자 이동
        AtomMove();

        // 충돌 원자 확인
        AtomBreak();

        // 종료 조건 확인
        if(Finish()) return;
    }
}

void AtomMove()
{
    int i, y,x,yy,xx,dir,energy;

    // 모든 원자들을 이동 시킴
    for(i=0; i<=N; i++)
    {
        yy=atom[i].y;  xx=atom[i].x;  dir=atom[i].dir;  energy=atom[i].energy;

        // 소멸된 원자인 경우  (에너지값 0인 경우)
        if(energy==0) continue;  // 건너뛴다

        // 소멸된 원자가 아닌 경우 (이동 시킴)
        y=yy+dy[dir];  x=xx+dx[dir];

        // 이동할 수 없는 경우
        if(OutOfRange(y,x)){atom[i].energy=0;  continue;}  // 맵을 벗어나는 경우 (소멸표시 - 에너지0)

        // 이동할 수 있는 경우
        map[yy][xx]=0;   // 이전 위치 지워줌
        atom[i].y=y;  atom[i].x=x;  // 이동한 위치로 정보 갱신
        if(map[y][x]!=0) map[y][x]=200;  else map[y][x]=atom[i].energy;   // 다른 원자 이미 위치해서. 충돌처리 필요한 경우 200 넣어줌
    }

    return;
}
void AtomBreak()
{
    int i,yy,xx,energy;

    // 원자 갯수 만큼만 for문 돔 (원자 위치정보에서. 확인할 map위치만 확인)
    for(i=0; i<=N; i++)
    {
        yy=atom[i].y;  xx=atom[i].x;  energy=atom[i].energy;

        // 소멸된 원자인 경우  (에너지값 0인 경우)
        if(energy==0) continue;  // 건너뛴다

        // 원자 위치에 2개 이상 있으면 제거.
        if( map[yy][xx] >= 200 ){ans += energy;  atom[i].energy=0;}   // 에너지 누적하고, 소멸 표시 해줌
    }

    // 원자 위치 모두 지워줌
    for(i=0; i<=N; i++){ yy=atom[i].y;  xx=atom[i].x;  map[yy][xx]=0;}  // 원자 위치,충돌 난 곳  모두 지워줌. 애초에 map은 충돌 확인용도다

    return;
}

bool Finish(){
    for(auto a : atom) if(a.energy != 0) return false;  // 소멸되지 않은 원자가 남아있는 경우.
    return true;  // 전부 소면된 경우.
}

bool OutOfRange(int y, int x){
    if(y<0 || x<0 || y>4000 || x>4000) return true;  // 범위를 벗어나는 경우
    return false;  // 범위를 벗어나지 않는 경우
}
