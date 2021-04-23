/* 오픈채팅방, kang-hyuck
  (구현)
  1. "전체대화내용"을 저장할 때, (id값,대화내용)으로 저장한다. 이 둘은 변하지 않는 고유한 값이다. "닉네임"만 따로 처리한다.
  2. Enter로 들어올 때마다 사용되는 "닉네임"을 id에 바로바로 갱신 해주면 된다.
*/
#include <string>
#include <vector>
#include <map>
#include <sstream>  // stringstream
using namespace std;

typedef struct CHAT{
    string id, contents;  // id,대화내용  (착안점 - 닉네임+대화내용 대신에. id+대화내용 적용)
}CHAT;

// 전역변수
vector<string> Record, ans;
map<string, string> IdToNickname;  // id값 넣으면 닉네임 반환
vector<CHAT> Action;  // 전체대화내용 저장용도 (id,대화내용) <- 이 둘은 절대로 변하지 않는 값이다. 닉네임만 변함
vector<string> act = {"님이 들어왔습니다.", "님이 나갔습니다."};

// 함수선언
void Start(void);

vector<string> solution(vector<string> record) {

    // 전역변수 초기화
    Record=record;

    // 실행부
    Start();

    // 출력부
    for(auto a : Action)  ans.push_back( IdToNickname[a.id] + a.contents );  // 닉네임 + 대화내용
    return ans;
}


void Start()
{
    stringstream ss;
    string cmd, id, nickname;
    int actionCnt=0;

    // 실행부
    for(auto s : Record)
    {
        ss.clear();  // ?? ss.str(s) 실행 뒤에. 반복문에서 s값이 바뀌어도. ss에 다시 s가 입력되지 않는다. ss.clear()로 앞 전 s 입력을 비워주어야함
        ss.str(s);   // stringstream에 문자열 넣음
        ss>>cmd;  // 커맨드 넣음

        // "전체 대화내용" 저장
        if(cmd=="Enter") {ss>>id;  ss>>nickname; IdToNickname[id]=nickname; Action.push_back({id,act[0]});}  // 들어올 때마다 해당 닉네임으로 변경
        if(cmd=="Leave") {ss>>id;  Action.push_back({id,act[1]});}
        if(cmd=="Change"){ss>>id;  ss>>nickname; IdToNickname[id]=nickname;}
    }
}
