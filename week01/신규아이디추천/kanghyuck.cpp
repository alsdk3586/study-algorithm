/* 신규 아이디 추천, kang-hyuck */
#include <iostream>
#include <string>
#include <vector>
using namespace std;


string solution(string new_id) {
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    string answer="", temp="";
    int i;
    
    
    // 1단계
    for(i=0; i<new_id.size(); i++)
        if(new_id[i] >= 'A' && new_id[i] <= 'Z')  // 대문자인 경우
            new_id[i] = new_id[i]-'A'+'a';  // 소문자로 바꿈

    // 2단계
    temp="";
    for(i=0; i<new_id.size(); i++)
        if( (new_id[i] >= 'a' && new_id[i] <= 'z') ||
            (new_id[i] >= '0' && new_id[i] <= '9') ||
             new_id[i]=='-' || new_id[i]=='_' || new_id[i]=='.' )
            temp.push_back(new_id[i]);
    new_id = temp;  // temp에 담았던 문자열을 new_id에 담음    

    // 3단계
    temp="";
    for(i=0; i<new_id.size(); i++)
        if(temp.back()=='.' && new_id[i]=='.') continue;  // '.'이 여러번 나오는 경우
        else temp.push_back(new_id[i]);   // '.'이 여러번 나오는 경우가 아닌 경우. 문자를 담는다.
    new_id = temp;  // temp에 담았던 문자열을 new_id에 담음
    
    // 4단계
    if(new_id.size()!=0  && new_id.front()=='.') new_id.erase(0,1);  // 처음 '.' 지움
    if(new_id.size()!=0  && new_id.back() =='.') new_id.pop_back();  // 마지막 '.' 지움
    
    // 5단계
    if(new_id.size()==0) new_id.push_back('a');
    
    // 6단계
    temp = "";
    if(new_id.size() >= 16){  // 문자열 길이가 16 이상인 경우.
        for(i=0; i<15; i++) temp.push_back(new_id[i]);  // 문자열 15개 넣음
        new_id = temp;  // temp에 담았던 문자열을 new_id에 담음
        if(new_id.size()!=0  && new_id.back() =='.') new_id.pop_back();  // 마지막 '.' 지움
    }
    
    // 7단계
    while(new_id.size() <= 2) new_id.push_back(new_id.back());  // 마지막 문자를 3이 될 때까지 넣는다
    
    
    // 출력부
    answer = new_id;
    
    return answer;
}
