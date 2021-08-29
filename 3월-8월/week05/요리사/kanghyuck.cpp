/* 요리사, kang-hyuck
  (완전탐색)
  1. 절반(N/2) 만큼 택해서, 2가지 요리를 만들면 된다. 1차원 check[] 배열에 해당 음식이 속하는 요리(1 or 0)인지 택해준다.
  2. 이중for문에서. check[] 값이 같은 얘들끼리 해당 인덱스 ij, ji값 누적하면 된다.
*/
#include <iostream>
#include <math.h>  // abs()
#include <algorithm>  // min()
using namespace std;
#define INF 987654321

// 전역변수
int T,N, ans;
int map[20][20];
int check[20];  // 1,0  2개 음식종류로 묶을때 사용

// 함수선언
void DFS(int, int);
int CheckAns(void);

int main()
{
    // 입력부
    cin>>T;  // 테스트 케이스 갯수
    for(int t=1; t<=T; t++)
    {
        cin>>N;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) cin>>map[i][j];  // Sij 입력
        
        // 실행부
        ans=INF;  // 정답값 INF로 초기화
        DFS(0,0);
     
        // 출력부
        cout<<"#"<<t<<" "<<ans<<endl;
    }
    
    return 0;    
}

void DFS(int cnt, int index)
{
    // 종료부
    if(cnt == N/2){ ans = min(ans, CheckAns());  return; }  // N/2만큼 선택한 경우
    if(index >= N) return;  // 선택 시작할 인덱스가 범위를 벗어나는 경우
    if(cnt > N/2) return;   // N/2 보다 많이 선택한 경우
    
    
    // 자식 노드 호출  (조합 구현)
    for(int i=index; i<N; i++)
    {
        check[i]=1;  // 해당 인덱스 1 표시
        
        DFS(cnt+1, i+1);
        
        check[i]=0;  // 해당 인덱스 1 제거
    }
}

int CheckAns()
{
    int food1=0, food2=0;
    
    // food1, food2 값 계산
    for(int i=0; i<N; i++) for(int j=0; j<N; j++){
        if( check[i]==1 && check[j]==1 ) food1 += map[i][j];
        if( check[i]==0 && check[j]==0 ) food2 += map[i][j];
    }
    
    // 종료부
    return abs(food1-food2);
}

