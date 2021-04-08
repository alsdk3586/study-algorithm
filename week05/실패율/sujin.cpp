#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(const vector<double>& v1, const vector<double>& v2) {
    if (v1[0] == v2[0]) return v1[1] < v2[1];
    return v1[0] > v2[0];
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<int> reachedPlayers(N, 0);  // 스테이지에 도달한 플레이어 수
    vector<int> losers(N, 0);  // 클리어하지 못한 사용자
    vector<vector<double>> failureInfo;  // [실패율, 인덱스]
    
    // failureInfo 초기화
    for (double idx = 0; idx < N; idx++) failureInfo.push_back(vector<double>{0, idx});
    
    // reachedPlayers, losers 설정
    for (auto& stage : stages) {
        for (int i = 0; i < stage && i < N; i++) reachedPlayers[i]++;
        if (stage != N + 1) losers[stage - 1]++;    
    }
    
    // failureInfo 설정
    for (int i = 0; i < N; i++) 
        if (reachedPlayers[i] == 0) failureInfo[i][0] = 0;
        else failureInfo[i][0] = losers[i] / (double) reachedPlayers[i];
    
    // 실패율을 기준으로 내림차순 정렬
    sort(failureInfo.begin(), failureInfo.end(), compare);
    
    // answer에 인덱스 추가
    for (auto& info : failureInfo) answer.push_back(info[1] + 1);

    return answer;
}
