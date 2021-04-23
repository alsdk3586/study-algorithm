#include <string>
#include <vector>

using namespace std;

// 정확성 : 통과
// 효율성 : 전부 실패 ㅜㅅㅜ
int solution(vector<int> food_times, long long k) {
	int answer = 0;
	int idx = 0; // 현재 먹으려는 음식 번호
	int cnt = 0; // 다 먹은 음식 수

	for (int i = 0; i < k;) { // k초까지
		if (idx >= food_times.size()) { // 인덱스 갱신(한 바퀴 돌았으면 다시 처음으로)
			idx -= food_times.size();
		}

		if (food_times[idx]) { // 음식이 있다면
			food_times[idx]--; // 음식 개수 감소
			if (food_times[idx] == 0) { // 다 먹었다면
				cnt++; // 다 먹은 음식 수 증가
			}
			idx++; // 다음 음식으로
			i++; // 시간 증가
		}
		else { // 음식이 없다면
			idx++; // 시간 증가없이 다음 음식번호로
		}

		if (cnt == food_times.size()) { // 모든 음식을 다 먹었다면 종료
			break;
		}
	}

	if (cnt == food_times.size()) { // 모든 음식을 다 먹었다면 -1
		answer = -1;
	}
	else {
		// 네트워크 복구 후 먹을 음식을 찾음
		while (1) {
			if (idx >= food_times.size()) { // 인덱스 갱신(한 바퀴 돌았으면 다시 처음으로)
				idx -= food_times.size();
			}

			if (food_times[idx]) { // 아직 남은 음식이 있다면 종료
				break;
			}
			else { // 없으면 다음 음식으로
				idx++;
			}
		}
		answer = idx + 1; // 인덱스와 음식번호 맞춤
	}

	return answer;
}