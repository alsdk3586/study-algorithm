#include <string>
#include <vector>

#include <iostream>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;

    // 골고로 큰 숫자들끼리 있어야 곱이 가장 클 것이다..
    if(n > s)
        return {-1};

    // 평균값으로 vector를 채워주고
    int ave = s / n;
    for(int i=0; i< n; i++)
        answer.push_back(ave);

    // 나머지 수는 나눠갖는다.
    int rem = s % n;
    auto itr = answer.end();
    for(int i=0; i<rem; i++) {
        itr--;
        (*itr)++;
    }

    return answer;
}

int main() {
    auto res = solution(2, 9);

    for(auto itr = res.begin(); itr != res.end(); itr++)
        std::cout << *itr << " ";
    

    return 0;
}