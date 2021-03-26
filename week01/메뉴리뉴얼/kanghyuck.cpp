/* 메뉴 리뉴얼, kang-hyuck */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<string, int> m;  // 해시 테이블, m["문자열"] = (갯수)
vector<string> v[15];  // v[문자열 크기]
int maxcnt[15];  // maxcnt[문자열 크기] = ("문자열 크기"에서 나온 "최댓 값")

void DFS(string, int, string);  // (문자열, 선택 인덱스, 만들어낸 문자열)

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);    
    
    
    // 해시 테이블 만들기
    for( auto s : orders ){
        sort(s.begin(), s.end());  // 주문받은 문자를 정렬 해준다 (예: "XWY"->"WXY")
        DFS(s, 0, "");
    }
    
    // 같은 "문자열 크기"를 갖는 문자 중에. "가장 카운트 값이 높은 값"을 저장
    for( auto key_cnt : m ){
        string key = key_cnt.first;   int cnt = key_cnt.second;
        maxcnt[key.size()] = max(maxcnt[key.size()],  cnt);  // max(최댓값으로 저장된 값, 해당 문자의 카운트 값)
    }
    
    // 벡터에 담기 (v[문자열 크기] 에 "문자열" 저장)
    for( auto key_cnt : m ){  
        string key = key_cnt.first;   int cnt = key_cnt.second;
        
        // 벡터에 담지 않는 경우
        if(cnt == 1) continue;  // "문자열"이 나온 "갯수"가 1이면 넘긴다
        if(maxcnt[key.size()] != cnt) continue;  // "문자열 최대 카운트값"과 다른 경우
        
        // 벡터에 담는 경우  (나온 갯수가 2이상인 경우)
        v[key.size()].push_back(key);  // v[문자열 크기] 에 문자열 저장
    }
    
    // course에 있는 "문자열 크기"에 대응되는 벡터에 있는 문자열만 모두 answer에 저장
    for( auto num : course )
        for( auto s : v[num] )
            answer.push_back(s);
    
    
    // answer에 있는 문자열들 순서 정렬
    sort(answer.begin(), answer.end());
    
    return answer;
}

void DFS(string s, int index, string made){
    
    // 조합 등록 (만들어낸 문자열 수 2 이상인 경우만 등록)
    if( made.size() >= 2 ) m[made]++;  // 해시 테이블에 해당 "문자" 갯수 카운트
    
    
    // 자식 노드 호출
    for(int i=index;  i<s.size();  i++)
    {
        made.push_back(s[i]);  // 인덱스에 해당하는 문자 넣음
            
        DFS(s, i+1, made);
            
        made.pop_back();  // 문자 꺼냄 (for문 돌아야 하므로!)
    }
}
