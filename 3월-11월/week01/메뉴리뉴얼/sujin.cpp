//
// Created by Sujin Kim on 21. 3. 15..
//

#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
map<string, int> comb;  // (코스 메뉴, 사용 횟수)
string target;  // 단품메뉴
bool chk[11];  // 조합을 만들 때, 각 메뉴를 사용할 수 있는지 저장

// idx   : target의 idx
// cnt   : 코스요리를 구성하는 단품메뉴들의 갯수
// menu  : 코스요리의 메뉴 구성
// '완전탐색(백트래킹)'으로 코스요리의 조합과 사용 횟수를 구한다.
void go(int idx, int cnt, string menu) {
    if (target.size() == idx) return;
    if (cnt == 0) {
        comb[menu]++;
        return;
    }
    for (int i = idx; i < target.size(); i++) {
        if (!chk[i]) {  // 해당 요리로 조합을 만들지 않은 경우
            chk[i] = 1;
            go(i, cnt - 1, menu + target[i]);
            chk[i] = 0;  // 백트래킹
        }
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    // order를 정렬함으로써 중복 제거
    for (string &order : orders)
        sort(order.begin(), order.end());

    for (int c : course) {
        // (코스 메뉴, 사용 횟수) 설정
        for (string order : orders) {
            memset(chk, 0, sizeof(chk));  // chk = {0, }로 초기화
            target = order;
            go(0, c, "");
        }

        // 사용 횟수가 2번 이상이면서 최대인 코스 메뉴만 answer에 추가한다.
        int maxCount = 0;
        for (auto it : comb)
            maxCount = max(maxCount, it.second);
        for (auto it : comb)
            if (maxCount >= 2 && it.second == maxCount)
                answer.push_back(it.first);

        comb.clear();
    }

    sort(answer.begin(), answer.end());
    return answer;
}