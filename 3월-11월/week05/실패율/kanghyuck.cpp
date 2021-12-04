/* 실패율, kang-hyuck 
  1. sort 사용시 vector<구조체>를 sort하려면. compare() 따로 정의 해야함
  2. sort 사용시 pair나 tuple사용하면 왼쪽멤버변수"순"으로 차례로 정렬 가능. compare() 따로 정의할 필요없음
*/
#include <string>
#include <vector>
#include <utility>  // pair<>
#include <algorithm>  // sort()
using namespace std;
/*
typedef struct STAGE{
    double successRate;  int stageNum;   // (성공률, 스테이지번호)
}STAGE;
*/
typedef pair<double,int> STAGE;  // (성공률, 스테이지번호)

// 전역변수
int people[200010];  // 스테이지에 머무는 사람 수
vector<STAGE> st;  // 정렬시 사용하는 벡터
vector<int> ans;
vector<int> Stages;
int n, poepleNum;

// 함수선언
void Start(void);

vector<int> solution(int N, vector<int> stages) {

    // 전역변수 초기화
    Stages=stages;   n=N;  poepleNum=stages.size();

    // 실행부
    Start();

    // 출력부
    for(int i=0; i<st.size(); i++) ans.push_back(st[i].second);  // 정렬된 스테이지 번호 담아준다
    return ans;
}

void Start()
{
    double successRate, nextTotalPeople;

    // 스테이지에 머무는 사람수 표시
    for(int i=0 ;i<Stages.size(); i++) people[Stages[i]]++;

    // 스테이지별 성공률 계산
    nextTotalPeople = poepleNum;  // 전체 인원 초기값으로 넣음
    for(int i=1 ;i<=n; i++)
    {
        // 성공률 계산
        successRate = (double)(nextTotalPeople - people[i])/nextTotalPeople;
        st.push_back({successRate, i});  // (성공률,스테이지 번호) 넣어준다

        // 다음 스테이지 총 도달인원 계산  (낮은단계에 있는 스테이지 인원 빼주면 됨)
        nextTotalPeople -= people[i];
    }

    // 정렬
    sort(st.begin(), st.end());
}
