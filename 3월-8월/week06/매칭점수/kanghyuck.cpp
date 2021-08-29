/* 매칭 점수, kang-hyuck
  (구현)
  1. string.find(검색할단어, 검색시작인덱스) 에서, "검색시작인덱스"가 string의 최대인덱스 보다 커도 실행가능하다.
  2. 문자열 ""안에서 문자 " 표현하려면 백슬래시 \ 붙여준다
*/
#include <string>
#include <vector>
#include <map>
#include <algorithm>  // sort()
using namespace std;

typedef struct PAGE{
    double matchScore;  int index;
}PAGE;

// 전역변수 선언
string Word;
vector<string> Pages;
string url[2]={ {"<meta property=\"og:url\" content=\"https://"}, {"<a href=\"https://"} };
int urlLen[2];
int ans;
map<string, int> basicScore; // [링크이름] = (기본점수)
map<string, double> externalLinkCnt;  // [링크이름] = (외부링크수)
map<string, vector<string>> inLinkName; // [링크A] = {링크A를 외부링크로 갖는 링크이름, }
map<int, string> indexToName;  // [페이지인덱스] = (링크이름)
vector<PAGE> pageSorted;

// 함수선언
void Start();
bool cmp(PAGE, PAGE);

int solution(string word, vector<string> pages) {
    
    // 전역변수 초기화
    Word=word;  Pages=pages;  urlLen[0]=url[0].size();  urlLen[1]=url[1].size();
    
    // 실행부
    Start();
    
    // 출력부
    sort(pageSorted.begin(), pageSorted.end(), cmp);  // 정렬
    ans = pageSorted[0].index;  // (가장 높은점수, 낮은 페이지인덱스)
    return ans;
}


void Start()
{
    // 1.기본점수, 2.외부링크점수 계산
    for(int num=0; num<Pages.size(); num++)  // 페이지 갯수만큼 확인
    {
        // 초기화
        int pos=0, cnt=0;  string page=Pages[num], name="";
        
        // "소문자" 변환
        for(int i=0; i<page.size(); i++) page[i]=tolower(page[i]);  // "페이지 문자" 모두 "소문자"로 변환
        for(int i=0; i<Word.size(); i++) Word[i]=tolower(Word[i]);  // "검색할 문자" 모두 "소문자"로 변환
        
        // 현재 페이지이름 찾기
        for(int i = page.find(url[0])+urlLen[0]; i<page.size(); i++)  // <a href=... 뒤에 나오는 "페이지이름"을 name에 저장.
            if(page[i]=='\"') break;  // 페이지이름 끝까지온 경우
            else name += page[i];  // 페이지이름 1문자씩 더함
        
        // 현재 페이지이름 등록
        indexToName[num]=name;  // (인덱스-페이지이름) 등록
        
        // 1. 기본점수
        while(1){
            // 단어검색
            pos = page.find(Word, pos+1);  // 찾은 인덱스 다음 인덱스 부터 검색 (검색 시작 위치 "인덱스 넘어가도 가능")
            
            // 종료 조건
            if(pos == string::npos) break; // 단어 더이상 없는 경우
            
            // 단어조건에 어긋나는 경우 (앞뒤로 다른 스펠링 단어 붙어 있는 경우..)
            if( ('a'<=page[pos-1] && 'z'>=page[pos-1]) || ('a'<=page[pos+Word.size()] && 'z'>=page[pos+Word.size()]) ) continue;
            // 기본점수 카운트
            basicScore[name]++;  // 현재페이지 "기본점수" 증가
        }
        pos=0;  // 검색시작위치 초기화
        
        // 2. 외부링크수
        while(1){
            // 외부링크검색
            pos = page.find(url[1], pos+1);  // 찾은 인덱스 다음 인덱스 부터 검색 (검색 시작 위치 "인덱스 넘어가도 가능")
            
            // 종료 조건
            if(pos == string::npos) break; // 외부링크 더이상 없는 경우
            
            // 외부링크 이름확인
            string externalName="";
            for(int i = pos+urlLen[1]; i<page.size(); i++)
                if(page[i]=='\"') break;  // 페이지이름 끝까지온 경우
                else externalName += page[i];  // 페이지이름 1문자씩 더함
            
            // 들어오는 링크이름 저장
            inLinkName[externalName].push_back(name);
            
            // 외부링크수 카운트
            externalLinkCnt[name]++;  // 현재페이지 "외부링크수" 증가
        }
    }
    
    // 3. 매칭점수 계산
    for(int num=0; num<Pages.size(); num++)  // 페이지 갯수만큼 확인
    {
        double score=0;   string name = indexToName[num];  // 인덱스 -> "이름" 가져옴
        
        // 매칭점수 계산
        score += (double)basicScore[name];  // 매칭점수 = (현재기본점수 + 연결된링크점수)
        for(auto s : inLinkName[name])  // 외부에서 들어오는 링크 모두 확인
            score += ((double)basicScore[s]/externalLinkCnt[s]);  // 링크점수 누적
        
        // 벡터에 담음 (나중에 정렬할 것임)
        pageSorted.push_back({score, num});  // (매칭점수, 페이지인덱스) 넣는다
    }
}

bool cmp(PAGE a, PAGE b){
    if(a.matchScore == b.matchScore) return a.index < b.index;  // 낮은 인덱스 부터.
    return a.matchScore > b.matchScore;  // 높은 매칭점수부터.
}
