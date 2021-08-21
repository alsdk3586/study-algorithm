#include <string>
#include <vector>

using namespace std;

string solution(int n) 
{
    string answer = "";
    int share = n;
    int remainder = -1;

    while (share != 0) 
    {
        //나머지, 몫 각각 저장
        remainder = share % 3;
        share = share / 3;

        //나누어 떨어지는 경우 몫을 1빼준다
        if (remainder == 0) 
        { 
            answer = "4" + answer;
            share--;
        }
        else if (remainder == 1) 
        {
            answer = "1" + answer;
        }
        else if (remainder == 2) 
        {
            answer = "2" + answer;
        }
    }

    return answer;
}