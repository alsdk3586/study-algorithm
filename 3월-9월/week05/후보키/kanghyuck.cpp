/* 후보키, kang-hyuck
  (비트마스크, 완전탐색) 
  1.유일성 - "선택한 속성조합"이 구성하고 있는 "행"이 유일한지 확인하기 위해 "map"사용
  2.최소성 - 선택한 속성 갯수 작은 얘(비트마스크에서 1인 "비트수" 작은 얘) 순으로 오름차순 정렬한 벡터에서
             DFS로 2개씩 갖는 모든 조합 경우의 수를 만들고 "서로 포함관계에 있는지" 확인 해보았음
             최소성을 갖지 않으면(다른 비트마스크 값에 포함되는 경우) check[] 배열값을 0으로 바꾸어 주었음
  3.("조합"을 사용해야 하는 경우) vs ("비트마스크"를 사용해야 하는 경우)
    - 선택 갯수가 "정해진 경우"(2개,3개,4개 등 "하나"로 정해져있는 경우):   "조합"(DFS) 사용
    - 선택 갯수가 "정해져있지 않는 경우"(0~N개 조합 모두 구해야하는 경우):  "비트마스크" 사용
  4.비트연산 주의할 점
    - (a&b == a) 랑 ((a&b) == a)랑 결과가 다르다... ㅠ.ㅠ "비트연산(&,^,...) 우선순위"가 "==" 연산우선 순위보다 느리다.
*/
#include <string>
#include <vector>
#include <map>
#include <utility>  // piar<,>
#include <algorithm> // sort()
using namespace std;

// 전역변수
int R,C, ans;
int check[1000];  // 최소성 판단(최대 2^8까지 주어짐)
vector<vector<string>> Relation;
vector<int> uniq;
vector<int> minimal;
vector<pair<int,int>> p;

// 함수선언
void DFS(int, int);
void CheckMinimality(void);
int Count(int);

int solution(vector<vector<string>> relation) {

    // 전역변수 초기화
    Relation = relation;   R=relation.size();   C=relation[0].size();

    // "유일성" 확인
    for(int i=0; i<(1<<C); i++)  // 모든 속성 조합 확인. (0:없음, 1: 있음)
    {
        // 행의 유일성 확인
        int notUniq=0;    map<string,int> m;  // 속성으로 만들어지는 행(문자열로 표현)이 유일한지 확인용도
        for(int j=0; j<R; j++)
        {
            string s="";

            // 존재하는 "속성" 마다 해당 j열 값 더해서 "문자열" 만든다
            for(int k=0; k<C; k++) if( i&(1<<k) ) s += Relation[j][k];

            // 만들어낸 "문자열" 값이 고유한 값인지 확인.
            if(m[s]==0) m[s]=1;  // 고유한 값인 경우 (map에 1 등록)
            else if(m[s]==1){notUniq=1; break;};     // 고유한 값이 아닌 경우 (다른 행을 더 확인 할 필요 없다)
        }

        // 행이 유일하지 않은 경우
        if(notUniq==1) continue;  // 다른 속성 조합 확인

        // 행이 유일한 경우
        uniq.push_back(i);  // 해당되는 속성 조합 저장
        check[i]=1;  // 최소성 판단 필요한 곳임을 등록
    }

    // "최소성" 확인  (조합으로 2개씩 선택한 뒤, 최소성 확인)
    for(int i=0; i<uniq.size(); i++) p.push_back({Count(uniq[i]), uniq[i]} );  // 벡터 p에 (비트수, 조합값) 을 넣는다
    sort(p.begin(), p.end());  // 비트수 작은것 부터 오름차순으로 p를 정렬한다. 조합으로 확인할 때, 비트수 작은 얘부터 선택해서 확인하기 위해서다.
    DFS(0,0);  // (0개선택, p의 0번인덱스부터 확인(조합 구현용 인자))

    // 출력부
    for(int i=0; i<(1<<C); i++) if(check[i]==1) ans++;  // 최소성 갖는 얘들(1 남은 얘들)만 정답 카운트
    return ans;
}


void DFS(int cnt, int index)
{
    // 종료부
    if(cnt==2){ CheckMinimality(); return; }
    if(index >= p.size()) return;

    // 자식 노드 호출
    for(int i=index; i<p.size(); i++)
    {
        // 최소성이 갖지 않는 경우 (uniq벡터에 등록된. 해당 속성쌍이 최소성을 갖지 않는 경우 의미)
        if(check[p[i].second]==0) continue;

        // 최소성을 갖는 경우
        minimal.push_back(p[i].second);
        DFS(cnt+1, i+1);
        minimal.pop_back();
    }
}

void CheckMinimality()
{
    int a=minimal[0], b=minimal[1];

    if((a & b) == a){check[b]=0; return;}  // ㅠ.ㅠ (a&b == a)랑 ((a&b)==a)랑 결과가 다르다.. "비트연산 우선순위"가 "==" 보다 느리다..
    if((a & b) == b){check[a]=0; return;}

    return;
}

int Count(int a){
    int cnt=0;
    while(a){ if(a&1==1)cnt++;  a=(a>>1); }  // 1인 비트 갯수 카운트
    return cnt;
}

