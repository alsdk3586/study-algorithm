#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 출력을 위한 정렬 : 실패율 기준 내림차순, 스테이지 번호 기준 오름차순
bool cmp(pair<double, int> f1, pair<double, int> f2) {
	return (f1.first == f2.first) ? (f1.second < f2.second) : (f1.first > f2.first);
}

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	vector<pair<double, int>> failRate; // <실패율, 스테이지 번호>
	int notClearCnt; // 도달했으나 클리어 못한 플레이어 수
	int reachCnt; // 도달한 플레이어 수

	for (int i = 1; i <= N; i++) { // 모든 스테이지 번호를 체크
		// 플레이어 수 초기화
		notClearCnt = 0;
		reachCnt = 0;
		for (int j = 0; j < stages.size(); j++) { // 모든 사용자 스테이지 번호를 탐색하며
			if (stages[j] >= i) { // 현재 스테이지를 클리어하거나 도달했다면
				reachCnt++; // 도달한 플레이어 수 증가
				if (stages[j] == i) { // 현재 스테이지에 도달만했다면
					notClearCnt++; // 클리어 못한 플레이어 수 증가
				}
			}
		}
		if (reachCnt == 0) { // 아무도 도달하지 못했으면
			failRate.push_back(make_pair(0.0, i)); // 실패율 0 저장
		}
		else {
			failRate.push_back(make_pair((double)notClearCnt / reachCnt, i)); // 실패율과 스테이지 번호 저장
		}
	}

	sort(failRate.begin(), failRate.end(), cmp);

	for (int i = 0; i < failRate.size(); i++) {
		answer.push_back(failRate[i].second);
	}

	return answer;
}