#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    int zero_count = 0;
    int win_count = 0;
    for(int i=0;i<lottos.size();i++)
        if(lottos[i] == 0) zero_count++; // 0이 몇개인가!
    //같은 숫자 체킹
    for(int i=0;i<win_nums.size();i++) 
        for(int j=0;j<win_nums.size();j++) 
            if(lottos[i] == win_nums[j]) win_count++;
    //범위 안에 들기 위해 count up
    if(win_count == 0) {
        win_count++;
        if(zero_count==6) zero_count--; //예외
    }
    //결과 입력
    answer.push_back(7-(win_count+zero_count));
    answer.push_back(7-win_count);
    return answer;
}