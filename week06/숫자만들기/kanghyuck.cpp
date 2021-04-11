/* 숫자 만들기, kang-hyuck
  (완전탐색)
  연산갯수 "전역변수"로 저장. "남은 연산갯수"에 따라서 자식노드 호출 유/무 판단.
*/
#include <iostream>
#include <algorithm> // min(), max()
using namespace std;
#define INF      987654321
#define NEGINF  -987654321

// 전역변수
int opCnt[4];
int a[15];
int T,N, ans, minVal,maxVal;

//
void DFS(int, int);
void Check(int);
int Cal(int, int, int);

int main()
{
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        // 입력부
        cin>>N;  // 숫자 갯수
        for(int i=0; i<4; i++) cin>>opCnt[i];  // 연산자 갯수 저장
        for(int i=0; i<N; i++) cin>>a[i];    // 사용할 값 저장
        minVal=INF;  maxVal=NEGINF;  // 초기화
    
        // 실행부
        DFS(1, a[0]);  // (1번인덱스 부터 선택, 0번인덱스 값)
    
        // 출력부
        ans = maxVal-minVal;
        cout<<"#"<<t<<" "<<ans<<endl;
    }
}

void DFS(int index, int val)
{
    // 종료부
    if(index == N){ Check(val); return; }  // 전부 선택한 경우
    
    // 자식 노드 호출
    for(int i=0; i<4; i++)
    {
        // 연산할 수 없는 경우
        if(opCnt[i]==0) continue;  // 해당 "연산자 갯수"가 부족한 경우
        
        // 연산할 수 있는 경우
        opCnt[i]--;  // 연산자 갯수 감소
        DFS(index+1, Cal(val, index, i));  // (선택할 인덱스, 연산 결과값)
        opCnt[i]++;  // 연산자 갯수 복구
    }
}

void Check(int val){
    minVal = min(minVal, val);  // 최솟값 갱신
    maxVal = max(maxVal, val);  // 최댓값 갱신
}

int Cal(int val, int index, int operand){
    if(operand==0) return  val + a[index];  // + 연산
    if(operand==1) return  val - a[index];  // - 연산
    if(operand==2) return  val * a[index];  // * 연산
    if(operand==3) return  val / a[index];  // / 연산
}

