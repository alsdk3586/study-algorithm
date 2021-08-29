/* 특이한 자석, kang-hyuck
  (완전탐색)
  1. 바퀴들의 "회전방향이 결정" 되고나서, "회전(Rotate())"이 이루어 져야한다. (Rotate()함수가 "자식 노드 호출" 부분 "뒤"에 나와야 한다)
     바퀴가 회전하기 '전' 맞닿아 있는 N/S극 상태에 따라 회전 유/무가 결정 되므로.
     따라서 DFS로 맨왼쪽바퀴(1번바퀴), 맨오른쪽바퀴(4번바퀴)까지 탐색해서 "회전방향부터 결정" 해야한다.
  2. 회전은 "덱" 사용 하면 쉽게 구할 수 있음
*/
#include <iostream>
#include <string.h>  // memset()
#include <deque>
using namespace std;

// 전역변수
int T,K;
deque<int> dq[5];
int dx[2] = {-1, 1};
int visited[5];

// 함수선언
void DFS(int, int);
void Rotate(int, int);

int main()
{
    int num,dir, temp;

    // 입력부
    cin>>T;  // 테스트 케이스
    for(int t=1; t<=T; t++)
    {
        cin>>K;  // 회전 횟수
        for(int i=1; i<=4; i++) for(int j=0; j<8; j++){cin>>temp; dq[i].push_back(temp);}    // 바퀴 날 정보
        
        // 실행부
        for(int i=0; i<K; i++){ cin>>num>>dir;  DFS(num, dir); memset(visited, 0, sizeof(visited)); }  // DFS 실행
        
        // 출력부
        cout<<"#"<<t<<" "<<(dq[1][0]*1 + dq[2][0]*2 + dq[3][0]*4 + dq[4][0]*8)<<endl;
        
        // 초기화
        for(int i=1; i<=4; i++) dq[i].clear();  // 톱니바퀴 정보 지워줌
    }


    return 0;
}

void DFS(int num, int dir)  // (현재바퀴번호, 현재바퀴에서 회전해야할 방향)
{
    // 종료부
    if( visited[num]==1 ) return;  // 방문 했던 경우

    visited[num]=1;  // 방문표시
    
    // 자식 노드 호출
    for(int i=0; i<2; i++)  // 0:왼쪽, 1:오른쪽 바퀴 회전 가능성 확인
    {
        int nextNum = num + dx[i];  // 다음 바퀴 번호 계산
        
        // 회전 시킬 수 없는 경우
        if( nextNum<1 || nextNum>4 ) continue;  // 바퀴번호 범위를 벗어나는 경우
        if( i==0 && dq[num][6]==dq[nextNum][2] ) continue; // 왼쪽 바퀴가 극성이 같은 경우
        if( i==1 && dq[num][2]==dq[nextNum][6] ) continue; // 오른쪽 바퀴가 극성이 같은 경우
    
        // 회전 시킬 수 있는 경우 (반대방향으로 회전)
        if(dir==  1) DFS(nextNum, -1);  // 반시계 방향으로 회전
        if(dir== -1) DFS(nextNum,  1);  // 시계 방향으로 회전
    }
    
    // 실행부
    Rotate(num,dir);  // 회전 (자신의 바퀴),  DFS로 양쪽 중 맨 끝 바퀴번호에 도달시 회전 시작.
}

void Rotate(int num, int dir)
{
    int temp;
    
    // 회전
    if(dir==  1){ temp=dq[num].back();  dq[num].pop_back();   dq[num].push_front(temp); }  // 시계방향  (맨 뒤 원소를 앞에 넣어줌)
    if(dir== -1){ temp=dq[num].front(); dq[num].pop_front();  dq[num].push_back(temp);  }  // 반시계방향(맨 앞 원소를 뒤에 넣어줌)
}

