#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int minDepth; // 가장 적은 투입한 친구 수

void dfs(int n, vector<int>& weak, vector<int>& dist, vector<int> weakChk, int depth, int repairCnt) {
	vector<int> tmpChk; // 취약 지점 점검 표시를 담은 배열을 임시 저장
	int tmpCnt; // 현재까지 점검된 외벽 수를 담은 변수
	int start; // 점검 시작 위치
	int end1; // 점검할 수 있는 최대 지점
	int end2 = -1;

	if (depth == dist.size()) { // 모든 친구를 이미 전부 투입했다면 리턴
		return;
	}

	for (int i = 0; i < weak.size(); i++) { // 취약 지점을 순회
		if (weakChk[i] == 1) { // 이미 점검되어있다면 넘어감
			continue;
		}
		tmpChk = weakChk;
		tmpCnt = repairCnt;
		start = weak[i]; // 점검 시작 위치 = i번 취약 지점 위치
		end1 = weak[i] + dist[depth]; // 점검 범위 = i번 취약 지점 ~ (i번 취약 지점 + depth번 친구의 이동거리)

		if (end1 >= n) { // 점검 범위가 전체 외벽 길이를 초과한다면 한 바퀴 돌아서 다음 지점까지 점검
			end2 = end1 - n; // n = 12, 10~13 지점까지 점검 가능 -> 10~12, 0~1 점검 가능
		}

		for (int j = 0; j < weak.size(); j++) { // 취약 지점을 순회
			if (tmpChk[j] == 0) { // 아직 점검되어있지 않은 취약 지점 중에
				if ((weak[j] >= start && weak[j] <= end1) || weak[j] <= end2) { // 현재 점검 범위안에서 점검 가능하다면
					tmpChk[j] = 1; // 점검 표시
					tmpCnt++; // 점검한 취약지점 개수 증가
				}
			}
		}

		if (tmpCnt == weak.size()) { // 전부 점검했다면
			minDepth = min(minDepth, depth); // 가장 적은 친구 투입 수로 갱신
		}

		// 현재 점검 상태, 투입한 친구 수, 점검한 취약 지점 개수를 기준으로 재귀
		dfs(n, weak, dist, tmpChk, depth + 1, tmpCnt);
	}
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	vector<int> weakChk(weak.size(), 0); // weakChk[i] = 1 -> weak[i]는 점검 완료

	minDepth = dist.size() + 1;

	sort(dist.begin(), dist.end(), greater<int>()); // 더 적은 수의 친구를 투입하기 위해 이동거리 기준 내림차순 정렬

	dfs(n, weak, dist, weakChk, 0, 0);

	if (minDepth == dist.size() + 1) { // 친구의 수보다 많은 수를 투입해야 점검 가능이면 -1
		answer = -1;
	}
	else {
		answer = minDepth + 1;
	}

	return answer;
}