https://yjyoon-dev.github.io/kakao/2021/01/30/kakao-menurenewal/
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int cnt[27]; // cnt[i]=n : 길이가 i인 조합 중 최대 주문 횟수는 n번
unordered_map<string, int> um; // um[str]=n : 조합 str의 주문 횟수는 n번
vector<string> menu[27][21]; // menu[i][j] : 길이가 i이고 j번 주문된 조합들의 목록

void comb(string s, int idx, string made) {
    if (made.size() > 1) { // 2번 이상 주문된 것만
        um[made]++; // 해당 조합 주문 횟수 누적
        cnt[made.size()] = max(cnt[made.size()], um[made]); // 조합 길이 별 최대 주문 횟수 갱신
        menu[made.size()][um[made]].push_back(made); // 분류별 조합 목록 추가
    }
    // 백트래킹
    for (int i = idx + 1; i < s.size(); i++) {
        made.push_back(s[i]);
        comb(s, i, made);
        made.pop_back();
    }
}
vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    // order의 모든 조합 전처리
    for (string& s : orders) {
        sort(s.begin(), s.end()); // 순서만 다르고 중복된 조합이 나오지 않도록 정렬
        comb(s, -1, "");
    }

    // 쿼리 수행
    for (int i : course)
        if (cnt[i] > 1) // 길이가 i인 조합의 최대 주문 횟수가 1 이상인 경우만
            for (string s : menu[i][cnt[i]])
                answer.push_back(s);

    sort(answer.begin(), answer.end());

    return answer;
}