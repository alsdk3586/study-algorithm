#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;
//초단위 배열을 생성하여 동시재생자수의 합을 구한 후, 
//인덱스 0 부터 광고시간까지 right를 1씩 증가하면서 해당 구간의 동시재생자수의 값이 가장 큰 구간의 인덱스에 광고를 재생한다.
//투포인터 알고리즘 & 슬라이딩 윈도우 알고리즘 사용

//시간을 초단위로 바꿔주어야 하므로 convert 함수 생성
int convert(string time)
{
    //문자열에서 필요한정보(숫자)만 빼내기 위해 stringstream 사용
    char tmp;
    int h, m, s;
    stringstream ss(time);

    ss >> h >> tmp >> m >> tmp >> s;

    //시간 -> 초단위로 변경
    return (h * 3600 + m * 60 + s);
}


string solution(string play_time, string adv_time, vector<string> logs) {

    int playTime = convert(play_time);
    int advTime = convert(adv_time);

    //구간합을 저장할 배열 만들기(초단위로 입력받으므로 최대100시간 * 3600)
    int totalSec[100 * 3600] = { 0 };
    for (string log : logs)
    {
        //logs에서 입력받은 log들을 하나씩 start와 end time 잘라서 초로 변경
        int start = convert(log.substr(0, 8));
        int end = convert(log.substr(9, 8));
            
        // start부터 end time까지 구간에 1씩 누적하기(재생한 구간이므로)
            for (int i = start; i < end; i++)
            {
                totalSec[i] += 1;
            }
    }

    //logs의 범위=30만, 동영상 재생시간 = 최대 36만초 
    //즉 currSum값이 Integer를 넘어서므로 64비트로 선언한다.
    long long currSum = 0;

    //0부터 advTime까지 돌면서 현재 광고시간 동안 동시재생자수의 합(currSum) 구하기
    for (int i = 0; i < advTime; i++)
    {
        currSum += totalSec[i];
    }
    //maxSum 을 currSum으로 초기화, maxIdx(구해야 할 시간대)선언
    long long maxSum = currSum;
    int maxIdx = 0;

    //이미 0부터 advTime 까지는 돌았으니 (52 line),
    //advTime 부터 playTime까지 오른쪽으로 한칸씩 이동하면서 currSum 구하기(슬라이딩 윈도우 알고리즘)
    for (int i = advTime; i < playTime; i++)
    {
        //현재 동시재생자수의 합(currSum) = currSum - totalSec[처음인덱스] + totalSec[다음인덱스]
        currSum = currSum - totalSec[i-advTime] + totalSec[i];

        //현재 누적합이 maxSum보다 크다면
        if (currSum > maxSum)
        {
            //maxSum에 currSum을 넣어준 후
            //max 인덱스 값에 광고시작 위치를 넣어준다.(광고는 1초부터 시작함)
            //**maxSum이 같을때, 빠른시각을 구해야 하는데 어차피 시작위치가 작은 것부터 시작하므로 상관없다.
            maxSum = currSum;
            maxIdx = i - advTime + 1;
        }
    }

    //초단위로 변경해서 구한 답을 다시 시간단위로 바꿔준다.
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", maxIdx / 3600, maxIdx / 60 % 60, maxIdx % 60);
    string answer = buf;
    return answer;
}