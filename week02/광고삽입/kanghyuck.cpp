/* 광고 삽입, kang-hyuck */
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

int play_time_int, adv_time_int;
int time_array[360010];
int ans_index, low,high;
long long ans,sum;  // 300,000 * 3,600*100... 100억 넘어갈 수 있을듯..? (17번 테스트 케이스)

int StringToInt(string, int);   // 시간(문자열), 0:시작시간/1:종료시간
string IntToString(int);

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";   int i,j,  logs_start,logs_end;


    // 시간을 int로 만들기 (초로 변환)
    play_time_int = StringToInt(play_time, 0);
    adv_time_int  = StringToInt(adv_time,  0);
    for(i=0; i<(int)logs.size(); i++){
        logs_start = StringToInt(logs[i], 0);
        logs_end   = StringToInt(logs[i], 1);
        for(j=logs_start; j<logs_end; j++) time_array[j]++;
    }


    // 투포인터 (합 최댓값 구하기)
    while(1)
    {
        // low,high 중 인덱스 증가
        if(high-low<=adv_time_int  &&  high<play_time_int) sum+=time_array[high++];
        else if(high-low>adv_time_int  &&  low<high) sum-=time_array[low++];
        else break;

        // 최댓값 확인 (광고 길이와 같은 경우만 갱신 확인)
        if(high-low==adv_time_int && ans<sum){ans=sum;  ans_index=low;}
    }


    // 출력부
    answer = IntToString(ans_index);
    return answer;
}


int StringToInt(string s, int mode){
    int h,m,sec, h_index,m_index,sec_index, ret;

    // 모드에 따른 index 지정
    if(mode==0){h_index=0; m_index=3;  sec_index=6; }
    else       {h_index=9; m_index=12; sec_index=15;}

    // 시간초 int로 변환
    h=stoi(s.substr(h_index,2))*3600;
    m=stoi(s.substr(m_index,2))*60;
    sec=stoi(s.substr(sec_index,2));

    // 반환
    return ret=h+m+sec;
}

string IntToString(int sec){
    string s;  char temp[5];
    sprintf(temp, "%02d", sec/3600);  s.append(temp);  s.push_back(':');
    sprintf(temp, "%02d", sec/60%60); s.append(temp);  s.push_back(':');
    sprintf(temp, "%02d", sec%60);    s.append(temp);  // 문자열을 붙일 때는 append 사용 (push_back은 문자만 가능)

    // 반환
    return s;
}
