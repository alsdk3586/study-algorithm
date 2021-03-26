/* 괄호 변환, kang-hyuck */
#include <string>
#include <vector>
using namespace std;

string Make(string);
int ParseBalance(string);
bool CheckRightString(string);
string Change(string);

string solution(string p) {
    string answer="";

    // 1단계
    if((int)p.size() == 0) return "";

    // 2단계
    answer = Make(p);

    return answer;
}

string Make(string w)
{
    string u,v;
    int i;

    // 2단계. 맨 처음 "균형잡힌 문자열" 나오는 경우, 마지막 인덱스 반환
    i = ParseBalance(w);

    // 빈문자열인 경우
    if(i==0) return "";

    // 빈문자열이 아닌 경우
    u = w.substr(0, i+1);   v = w.substr(i+1, w.size());

    // 3단계
    if(CheckRightString(u)) return u + Make(v);

    // 4단계
    return "(" + Make(v) + ")" + Change(u);

}

int ParseBalance(string w)
{
    int i, cnt=0;

    for(i=0; i<(int)w.size(); i++)
    {
        //  갯수 카운트 ('(' or ')')
        if(w[i]=='(') cnt++; else cnt--;
        if(cnt==0) return i;  // 맨 처음 "균형잡힌 문자열" 나오는 경우. 마지막 인덱스 반환
    }

    return 0;
}

bool CheckRightString(string u)
{
    int i, cnt=0;

    for(i=0; i<(int)u.size(); i++){
        if(u[i]=='(') cnt++; else cnt--;
        if(cnt<0) return false;  // )가 ( 보다 먼저 나오는 경우가 1번이라도 존재한다면. 거짓
    }

    return true;
}

string Change(string u)
{
    string s;
    int i;

    // u의 첫번째, 마지막 문자 제거
    u.erase(0,1);  u.pop_back();  // string.erase(인덱스, 갯수)

    // (,) 방향 바꾸어 주기
    for(i=0; i<(int)u.size(); i++)
        if(u[i]=='(') s.push_back(')');
        else s.push_back('(');

    return s;
}
