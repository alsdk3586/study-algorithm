#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define MAX 10001

map<string,int> m;
int parent[MAX];
int profits[MAX];

void divideProfit(int indx, int profit) {
    if(indx == -1) return; //최상위 포식자면 종료

    int stolen = profit/10; //10%를 상위 포식자에게 준다
    profits[indx] += profit - stolen; //내 이익

    if(!stolen) return; //줄 profit이 없다면 stop

    divideProfit(parent[indx], stolen); //재귀
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;

    for (int i = 0; i < enroll.size(); i++)
        m[enroll[i]] = i; //name, index 저장

    for (int i = 0; i < referral.size(); i++) {
        if (referral[i] == "-") parent[i] = -1; //최상위 포식자
        else parent[i] = m[referral[i]]; //상위 포식자 저장
    }
 
    for (int i = 0; i < seller.size(); i++)
        divideProfit(m[seller[i]], amount[i] * 100); // 이익 계산(칫솔 개당 100원)
 
    for (int i = 0; i < enroll.size(); i++)
        answer.push_back(profits[i]); //결과
 
    return answer;
}
