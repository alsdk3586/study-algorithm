/* 순위 검색, kang-hyuck */
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>  // sort()
#include <iostream>
#include <sstream>
using namespace std;
unordered_map<string, int> m;  // 문자열 -> 정수(인덱스)
vector<int> people[4][3][3][3];   // people[개발언어][직군][경력][소울푸드] = 점수

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    int i,j,k,l, score;   string lang, position, career,soulfood;


    // (string -> 정수) 변환 해시테이블 생성
    m["-"] = 0;  // 쿼리에서 사용
    m["cpp"]=1;  m["java"]=2; m["python"]=3;
    m["backend"]=1;  m["frontend"]=2;
    m["junior"]=1;  m["senior"]=2;
    m["chicken"]=1;  m["pizza"]=2;


    // 문자열 마다 다차원 배열에 값 저장
    for( auto s : info ){
        // stringstream에 문자열 입력
        stringstream ss(s);    //  컴파일러 차이? - ss.str(s) 로 하면 s가 안바뀐다..

        // 문자열에서 문자 파싱
        ss>>lang>>position>>career>>soulfood>>score;
        int temp[4] = { m[lang], m[position], m[career], m[soulfood] };  // 원본 배열 생성(점수가 저장 될 index)

        // 비트마스킹 + 점수저장
        int temp2[4] = {0, };  // 비트마스킹을 위한 배열 생성 (원본 배열 원소값 저장)
        for(i=0; i<16; i++){   // 비트값(0000~1111)에 대응되는 temp2[] 배열 원소값 생성
            for(j=0; j<4; j++){   // 1bit 씩 1/0 확인
                temp2[j] = 0;  // 0값으로 초기화
                if(i&(1<<j)) temp2[j] = temp[j];  // 1일 경우 "원본 배열 원소값" 저장
            }

            // 만들어낸 temp2[] 배열 원소값(index)을 이용하여 해당 위치에 점수 저장
            people[temp2[0]][temp2[1]][temp2[2]][temp2[3]].push_back(score);  // 점수 저장
        }
    }


    // 점수값 정렬 (오름차순)
    for(i=0; i<4; i++) for(j=0; j<3; j++) for(k=0; k<3; k++) for(l=0; l<3; l++)
        sort(people[i][j][k][l].begin(), people[i][j][k][l].end());


    // 이분 탐색
    for( auto s : query ){
        // stringstream에 문자열 입력
        stringstream ss(s);  string temp; // and문자 temp에 담음

        // 문자열에서 문자 파싱
        ss>>lang>>temp>>position>>temp>>career>>temp>>soulfood>>score;

        // 인원수 저장
        int index = lower_bound(people[m[lang]][m[position]][m[career]][m[soulfood]].begin(), people[m[lang]][m[position]][m[career]][m[soulfood]].end(), score) - people[m[lang]][m[position]][m[career]][m[soulfood]].begin();  // "이상인 값"이 나오는 인덱스를 바이너리 서치로 찾는다
        answer.push_back(people[m[lang]][m[position]][m[career]][m[soulfood]].size() - index);  // 인원수 저장
    }


    // 출력부
    return answer;
}
