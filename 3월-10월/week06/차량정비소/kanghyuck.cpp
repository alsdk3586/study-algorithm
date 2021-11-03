/* 차량 정비소, kang-hyuck
  (구현)
  크게 2가지 단계로 나눌 수 있다. (1.창구사용 끝난사람 제거,  2.창구사용 필요한사람 채워넣기)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>  // memset()
using namespace std;

typedef struct CusInfo{
    int rec, rep, recFinTime, repFinTime, fin;
}CusInfo;

// 전역변수 선언
int T,N,M,K,A,B;
int ai[15], bi[15];  // ai:접수처리시간, bi:고장처리시간
int tk[1010];  // tk:도착시간
CusInfo customer[1010];  // 고객정보
int usedReception[15], usedRepair[15];
queue<int> qReception, qRepair;
int ans;

// 함수선언
void Start();
void Reset();  // 전역변수 초기화
void WaitingReception(int);  // 도착    ->  접수줄
void WaitingRepair(int);     // 접수창구 ->  정비줄
void RemoveCus(int);         // 정비창구 ->  끝
void Reception(int);         // 접수줄  ->  접수창구
void Repair(int);            // 정비줄  ->  정비창구
bool Finish();  // 시뮬레이션 종료조건 확인

int main()
{
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        // 입력부
        cin>>N>>M>>K>>A>>B;
        for(int i=1; i<=N; i++) cin>>ai[i];  // 접수처리시간 저장
        for(int i=1; i<=M; i++) cin>>bi[i];  // 고장처리시간 저장
        for(int i=1; i<=K; i++) cin>>tk[i];  // 도착시간 저장
        Reset(); // 전역변수 초기화
    
        // 실행부
        Start();
    
        // 출력부
        for(int i=1; i<=K; i++) if(customer[i].rec==A && customer[i].rep==B) ans+=i;  // 점수계산
        if(ans==0)cout<<"#"<<t<<" -1"<<endl;  // 해당 고객이 없는 경우 -1 출력
        else      cout<<"#"<<t<<" "<<ans<<endl;  // 해당 고객 있는 경우 점수출력
    }


    return 0;
}

void Start()
{
    // 시뮬레이션 시작
    int time=0;
    while(1)
    {
        // 창구인원 제거 (사용 끝난사람)
        WaitingReception(time); // 접수 줄세우기
        WaitingRepair(time);    // 정비 줄세우기
        RemoveCus(time);        // 정비 끝난사람 제거
        
        // 창구인원 채우기
        Reception(time);  // 접수창구 채우기
        Repair(time);     // 정비창구 채우기
    
        // 종료조건 확인
        if(Finish()) return;
        
        // 시간 증가
        time++;
    }
}

void WaitingReception(int time){
    // 도착한 고객 큐에 넣어줌 (접수줄 채우기)
    for(int i=1; i<=K; i++) if(tk[i]==time) qReception.push(i);  // (해당시간 == 도착시간)인 고객 넣음
}
void WaitingRepair(int time){
    // 접수창구 끝난 사람 확인 (접수창구 -> 정비줄)
    for(int i=1; i<=N; i++)
    {
        int cusNum = usedReception[i];
    
        // 접수가 안끝난 경우
        if(usedReception[i]==0) continue;  // 비어있는 경우
        if(time != customer[cusNum].recFinTime) continue;  // 시간이 다 안된경우
        
        // 접수가 끝난경우
        qRepair.push(cusNum);  // "정비줄"에 넣어줌
        usedReception[i]=0;  // 접수창구 비워줌
    }
}
void RemoveCus(int time){
    // 정비창구 끝난 사람 확인 (정비창구 -> 끝)
    for(int i=1; i<=M; i++)
    {
        int cusNum = usedRepair[i];
    
        // 정비가 안끝난 경우
        if(usedRepair[i]==0) continue;  // 비어있는 경우
        if(time != customer[cusNum].repFinTime) continue;  // 시간이 다 안된경우
        
        // 정비가 끝난경우
        customer[cusNum].fin=1;  // 끝났음 표시
        usedRepair[i]=0;  // 접수창구 비워줌
    }
}
void Reception(int time)
{
    // 접수창구 사용 가능한 곳 확인 (접수줄 -> 접수창구)
    for(int i=1; i<=N; i++)
    {
        // 접수할 수 없는 경우
        if(usedReception[i] != 0) continue;  // 접수창구 사용중인 경우
        if(qReception.empty()) return;  // 줄서있는 고객이 없는 경우
        
        // 접수할 수 있는 경우
        int cusNum = qReception.front();  qReception.pop();  // 맨 앞 고객 번호
        usedReception[i] = cusNum;  // 사용중 표시 ("고객 번호" 저장)
        customer[cusNum].rec = i;   // 고객이 사용한 "접수창구 번호" 저장
        customer[cusNum].recFinTime = time + ai[i];  // "접수 끝나는 시간" 저장
    }   
}
void Repair(int time)
{
    // 정비창구 사용 가능한 곳 확인 (정비줄 -> 정비창구)
    for(int i=1; i<=M; i++)
    {
        // 접수할 수 없는 경우
        if(usedRepair[i] != 0) continue;  // 정비창구 사용중인 경우
        if(qRepair.empty()) return;  // 줄서있는 고객이 없는 경우
        
        // 접수할 수 있는 경우
        int cusNum = qRepair.front();  qRepair.pop();  // 맨 앞 고객 번호
        usedRepair[i] = cusNum;  // 사용중 표시 ("고객 번호" 저장)
        customer[cusNum].rep = i;   // 고객이 사용한 "정비창구 번호" 저장
        customer[cusNum].repFinTime = time + bi[i];  // "정비 끝나는 시간" 저장
    }   
}
bool Finish(){
    // 모든 고객 확인 (정비가 끝났는지)
    for(int i=1; i<=K; i++) if(customer[i].fin == -1) return false;  // 정비를 못받은 고객이 있는 경우 (-1)
    return true;  // 정비를 못받은 고객이 없는 경우
}
void Reset(){
    ans=0;  // 정답 초기화
    memset(customer, -1, sizeof(customer));  // 고객정보 초기화 (-1)
    memset(usedReception, 0, sizeof(usedReception));  // 접수창구 사용정보 초기화 (0)
    memset(usedRepair, 0, sizeof(usedRepair));        // 정비창구 사용정보 초기화 (0)
    while(!qReception.empty()){qReception.pop();}  while(!qRepair.empty()){qRepair.pop();}  // 접수줄,정비줄 큐 비우기
}

