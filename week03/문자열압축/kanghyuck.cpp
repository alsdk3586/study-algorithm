/* 문자열 압축, kang-hyuck */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int Simulation(int, string);
int CanGrouping(int, int, int);
int Grouping(int,  int,  string,  int*);

int solution(string s) {
    int i, answer = 987654321;

    // 실행부
    for(i=1; i<=(int)s.size(); i++)
        answer = min(answer,  Simulation(i, s));

    // 출력부
    return answer;
}


int Simulation(int groupSize, string s){

    int i,j,num=1,nextI=0;   string str;

    // 실행부
    for(i=0;  i<(int)s.size();  i=nextI) // 안묶이기 시작하는 인덱스가 nextI
    {
        // 그룹핑을 할 수 없는 경우
        if( -1 == CanGrouping(i, groupSize, s.size()) ) break;

        // 그룹핑을 할 수 있는 경우
        num = Grouping(i, groupSize, s,  &nextI);  // 묶은 갯수 반환, 안묶이기 시작하는 인덱스 부분 반환

        // 그룹핑 결과 반영
        if(num != 1) str.append( to_string(num) );  // 숫자 넣어준다
        for(j=i;  j<i+groupSize; j++) str.push_back(s[j]);  // 문자열 넣어준다  (i+groupSize-1 까지 for문 돌림)
    }

    // 묶고 남은 얘들 붙여줌
    if(i<(int)s.size()) for(j=i; j<(int)s.size(); j++) str.push_back(s[j]); // i가 s.size() 보다 작다면 남았을테니
    return (int)str.size();  // return값 안넣었더니... core dump뜸
}


int CanGrouping(int index, int groupSize, int stringSize){
    if( index+groupSize-1 >= stringSize ) return -1;  // 그룹핑 할 수 없는 경우(묶음의 "마지막 인덱스">=stringSize)
    return 1;  // 그룹핑 할 수 있는 경우
}

int Grouping(int index, int groupSize, string s,  int * nextI){
    int i, cnt=1;
    string original = s.substr(index, groupSize);  // 맨 처음 묶음

    // 비교한다 (goupSize만큼 이동하면서,  맨처음 묶음이랑 비교해본다)
    for(i=index+groupSize;  i<s.size();  i+=groupSize){
        if( 0 != original.compare(s.substr(i, groupSize)) ) break;  // 다른 문자 나오면 나옴
        cnt++;  // 같은 모양의 묶음이였다면 증가
    }

    // 종료부
    *nextI = i;  // 다음에 그룹핑 조사할 index. (이 i 부터 다른 묶음이라서 break 됬을테니.)
    return cnt;  // 묶음 갯수 반환
}
