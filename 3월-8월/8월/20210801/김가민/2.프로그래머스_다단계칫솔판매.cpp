#include<iostream>
#include<unordered_map>
#include<algorithm>
//추천인과 연결되어 수익을 얻는 구조이므로 DFS알고리즘 사용
using namespace std;
//추천인을 넣을 map
unordered_map<string, string> tree;
//각 맴버별 수익을 넣을 map
unordered_map<string, int> member;

void dfs(string& name, int price)
{
    //10퍼센트를 수익금으로 가지므로 10으로 나눠준다.
    int nextprice = price / 10;
    //해당 멤버는 원가에서 수익금을 뺀 금액만큼 가짐
    member[name] += price - nextprice;
    //추천인이 없거나 10퍼센트를 계산한금액이 1원미만인 경우는 리턴
    if (name == "-" || nextprice == 0)
    {
        return;
    }
    dfs(tree[name], nextprice);
}
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) 
{
    vector<int> answer;
    //referral 내에서 i 번째에 있는 이름은 배열 enroll 내에서 i 번째에 있는 판매원을 조직에 참여시킨 사람의 이름이므로 아래와 같이 정의해준다.
    for (int i = 0; i < enroll.size(); i++) 
    {
        tree[enroll[i]] = referral[i];
    }
    //판매한 수량 만큼 dfs를 돌려준다. 
    for (int i = 0; i < seller.size(); i++) 
    {
        dfs(seller[i], amount[i] * 100);
    }
    //각 맴버별 이익만큼 member로 선언한 map에 담아주고 마지막에 출력해준다.
    for (int i = 0; i < enroll.size(); i++)
        answer.push_back(member[enroll[i]]);
    return answer;
}